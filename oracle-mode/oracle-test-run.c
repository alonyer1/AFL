#define _GNU_SOURCE
#define RUN_CODE

#ifdef RUN_CODE

//#define USER_FUNCTION func2
#endif
#include <stdbool.h>
//#include "../oracle-run.h"
#include <unistd.h>
#include <sched.h>
#include "msr-utils2.h"
#include <string.h>
#define USER_FUNCTION (func2)

extern void dwall();
extern int func(char* input_str);
extern int func2(char* input_str);
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;
#define FIRST_ITERATIONS 100
#define DO_SYS( call, error ) if((call)==-1) { perror(error); exit(-1); }
#define DO_SYS2( result, errval, call, error ) { result = (call); if((result)==(errval)) { perror(error); exit(-1); }}
#define ERR_AFFINITY "Error: cannot isolate core affinity."
#define ISOLATED_CORE 3
#define REG_SIZE 64
#define CACHELINE_SIZE 64
#define STRLEN 12
#define WRITE "w"
/* Efficient functions to use in measuring at the beginning and end. */

//extern void btb_override();

static inline uint64_t measure_start() {
    uint32_t cycles_low=0, cycles_high=0;
    asm volatile ("CPUID\n\t" "RDTSC\n\t" : "=a" (cycles_low), "=d"(cycles_high):: "%rbx", "memory");
    return (((uint64_t)cycles_high << 32) | cycles_low);
}


static inline uint64_t measure_end() {
    uint32_t cycles_low=0, cycles_high=0, aux=0;
    asm volatile ("RDTSCP\n\t" : "=a" (cycles_low), "=d"(cycles_high), "=c"(aux):: "%rbx", "memory");
    return (((uint64_t)cycles_high << 32) | cycles_low);
}

inline uint64_t dan_get_cycles() {
    unsigned int a, d;
    asm volatile("rdtsc" : "=a" (a), "=d" (d) :: "memory");
    return ( ((unsigned long)a) | (((unsigned long)d)<<32) );
}

/* Measure floor of log_2 efficiently. */
static inline uint64_t log_2(uint64_t var) {
    uint64_t res = 0;
    asm ("BSRQ %1, %0" : "=r"(res) : "r"(var));
    return res;
}

/* Move process to isolated core. */
static inline void set_core(int core_num) {
    cpu_set_t core_mask;
    __CPU_ZERO_S (sizeof (cpu_set_t), &core_mask);
    __CPU_SET_S (ISOLATED_CORE, sizeof (cpu_set_t), &core_mask);
    DO_SYS(sched_setaffinity(0, sizeof(core_mask), &core_mask), ERR_AFFINITY)
}

/* Measure code once. If argument is true, measure a function provided by macro.*/
static inline uint64_t run_and_measure(char* arg) {
    uint64_t start = measure_start();
    USER_FUNCTION(arg);
    uint64_t end = measure_end();
    return end-start;
}
void free_strlist(int length, char** list) {
    for(int i=0; i<length; i++) free(list[i]);
    free(list);
}
char** get_inputs(const char* input_path, int* line_count) {
    FILE* file;
    DO_SYS2(file, NULL, fopen(input_path, "r"), "Failed to open input file.")
    char* line = NULL;
    size_t len = 0;
    ssize_t have_read=0;
    // Count the number of lines in the file
    *line_count = 0;
    while ((have_read = getline(&line, &len, file)) != -1) {
        (*line_count)++;
    }
    rewind(file);
    // Allocate an array of string pointers
    char** list = (char**) valloc(sizeof(char*) * (*line_count));
    if(list==NULL) {
        perror("Failed to allocated.\n");
        exit(-1);
    }

    // Read the file again, line by line
    for(int i=0; ((have_read = getline(&line, &len, file)) != -1); i++) {
        // Remove newline character, if present
        if (line[have_read - 1] == '\n') {
            line[have_read - 1] = '\0';
            have_read--;
        }

        // Allocate memory for the line in the list
        list[i] = (char*) valloc(have_read + 1);
        if(list[i]==NULL) {
            perror("Failed to allocated.\n");
            exit(-1);
        }
        // Copy the line to the list
        strcpy(list[i], line);
    }
    // Cleanup
    free(line);
    fclose(file);
    return list;
}

/* Perform a loop of measurements. */
void run_loop_histogram(const char* input_path, const char* output_path, int loop_n) { 
    //Isolate core.
    set_core(ISOLATED_CORE);
    long unsigned int histogram[REG_SIZE] = {0};
    //Create an array of inputs from file, every line corresponds to different input.
    int num_inputs=0;
    char** inputs = get_inputs(input_path, &num_inputs);
    /* loop_n iterations:
    1. "dwall" resets the branch predictors.
    2. run_and_measure measures func from start to finish.
    3. highest set bit of the result is stored in histogram. */
    uint64_t log_result=0,time_measured=0;
    uint64_t average_measurement_time = 0;
    for(int i=0; i < loop_n; i++) {
        //dwall();
        time_measured = run_and_measure(inputs[0]);
        average_measurement_time+=time_measured;
        log_result = log_2(time_measured);
        histogram[log_result]++;
    }
    /* Print to a file the results of the histogram. */
    FILE * out_file;
    out_file = fopen(output_path, "w");
    if(out_file == NULL) {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_measurement_time/((float)loop_n));
    for (int i = 0; i < REG_SIZE; i++) {
        fprintf(out_file, "%lu\n", histogram[i]);
    }
    fclose(out_file);
    free_strlist(num_inputs, inputs);
}
void run_loop(const char* input_path, const char* output_path, int loop_n) { 
    //Isolate core.
    set_core(ISOLATED_CORE);
    uint64_t* results = (uint64_t*) valloc(loop_n * sizeof(uint64_t));
    if(results == NULL) {
        perror("Failed to allocate.\n");
        exit(-1);
    }
    // Create an array of inputs from file. We only use the first line on a file, inputs[0].
    int num_inputs=0;
    char** inputs = get_inputs(input_path, &num_inputs);
    uint64_t time_measured=0;
    uint64_t average_measurement_time = 0;
    /* loop_n iterations:
    1. use function "dwall" to reset branch predictors.
    2. run_and_measure calls func and measures cycles from before to after call.
    3. result is stored in the array.
    */
    for(int i=0; i < loop_n; i++) {
        dwall();
        time_measured = run_and_measure(inputs[0]);
        average_measurement_time+=time_measured;
        results[i] = time_measured;
    }
    /* Print results to file. */
    FILE * out_file;
    out_file = fopen(output_path, "w");
    if(out_file == NULL) {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_measurement_time/((float)loop_n));
    for (int i = 0; i < loop_n; i++) {
        fprintf(out_file, "%lu\n", results[i]);
    }
    fclose(out_file);
    free_strlist(num_inputs, inputs);
    free(results);
}

inline void clflush(volatile void* address) {
    asm volatile("clflush (%0)\n\t" :: "r"(address) : "memory");
}

void run_loop_cache(const char* input_path, const char* output_path, int loop_n) { 
    //Isolate core.
    set_core(ISOLATED_CORE);
    uint64_t* results = (uint64_t*) valloc(loop_n * sizeof(uint64_t));
    if(results == NULL) {
        perror("Failed to allocate.\n");
        exit(-1);
    }

    // Create an array of inputs from file. We only use the first line on a file, inputs[0].
    // We use that line to create "big_input" a string where ever cache line represents one char from inputs[0].
    int num_inputs=0;
    char** inputs = get_inputs(input_path, &num_inputs);
    uint64_t time_measured=0;
    uint64_t average_measurement_time = 0;
    char* big_input = (char*)valloc(STRLEN*CACHELINE_SIZE);
    if(!big_input) {perror("Failed to allocate.\n"); exit(-1);}
    for(int i=0; i< STRLEN*CACHELINE_SIZE;i++) big_input[i]='a';
    for(int i=0; i < STRLEN; i++) {
        big_input[i*CACHELINE_SIZE] = inputs[0][i];
    }

    /* loop_n iterations:
    1. flush the cache lines.
    2. run_and_measure calls func2 and measures cycles from start to finish.
    3. result is stored in the array.
    */
    for(int i=0; i < loop_n; i++) {
        for(int j=0; j<STRLEN; j+=CACHELINE_SIZE) {
            clflush(big_input+j);
        }
        asm volatile("mfence" ::: "memory");
        time_measured = run_and_measure(big_input);
        average_measurement_time+=time_measured;
        results[i] = time_measured;
    }
    /* Print all results to a file. */
    FILE * out_file;
    out_file = fopen(output_path, WRITE);
    if(out_file == NULL) {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_measurement_time/((float)loop_n));
    for (int i = 0; i < loop_n; i++) {
        fprintf(out_file, "%lu\n", results[i]);
    }
    // Free structures.
    fclose(out_file);
    free_strlist(num_inputs, inputs);
    free(big_input);
    free(results);
}

int main(int argc, const char** argv) {
    if(argc !=4) printf("Correct usage: ./oracle <inputs-file> <output-file> <iteration-count>\n");
    else run_loop_cache(argv[1], argv[2], atoi(argv[3]));
}