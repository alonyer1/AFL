#define _GNU_SOURCE
#define RUN_CODE

#ifdef RUN_CODE
#include "user-code-test.h"
//#include "test-program.h"
#define USER_FUNCTION func
#endif
#include <stdbool.h>
//#include "../oracle-run.h"
#include <unistd.h>
#include <sched.h>
#include "msr-utils2.h"
#include <string.h>

//extern void dwall();
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;
#define FIRST_ITERATIONS 100
#define DO_SYS( call, error ) if((call)==-1) { perror(error); exit(-1); }
#define DO_SYS2( result, errval, call, error ) { result = (call); if((result)==(errval)) { perror(error); exit(-1); }}
#define ERR_AFFINITY "Error: cannot isolate core affinity."
#define ISOLATED_CORE 3
#define REG_SIZE 64

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

static inline uint64_t dan_get_cycles() {
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
static inline uint64_t measure_instance2(bool with_code, char* arg) {
    uint64_t start=0, end=0;
    if(with_code) {
        start = dan_get_cycles();
        (USER_FUNCTION)(arg);
        end = dan_get_cycles();
    } else {
        start = dan_get_cycles();
        end = dan_get_cycles();
    }
    return end-start;
}
void free_strlist(int length, char** list) {
    for(int i=0; i<length; i++) free(list[i]);
    free(list);
}
char** input_arr(const char* input_path, int* line_count) {
    FILE* file;
    char** list;
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
    DO_SYS2(list, NULL, (char**)malloc(sizeof(char*) * (*line_count)), "Failed to allocate.")
    // Read the file again, line by line
    for(int i=0; ((have_read = getline(&line, &len, file)) != -1); i++) {
        // Remove newline character, if present
        if (line[have_read - 1] == '\n') {
            line[have_read - 1] = '\0';
            have_read--;
        }

        // Allocate memory for the line in the list
        DO_SYS2(list[i], NULL, (char*)malloc(sizeof(char) * (have_read + 1)), "Failed to allocate.")
        // Copy the line to the list
        strcpy(list[i], line);
    }
    // Cleanup
    free(line);
    fclose(file);
    return list;
}

/* Perform a loop of measurements. */
void measure_loop(const char* input_path, const char* output_path, int loop_n) { 
    //Isolate core.
    set_core(ISOLATED_CORE);
    long unsigned int histogram[REG_SIZE] = {0};
    //Create an array of inputs from file.
    int num_inputs=0;
    char** inputs = input_arr(input_path, &num_inputs);
    uint64_t log_result=0,time_measured=0;
    //prediction_wall();
    uint64_t average_measurement_time = 0;
    //uint64_t measurement_cycles = measure_instance2(false, NULL);

    /* Outer loop. Performs measurement and stores the log in histogram. */
    for(int i=0; i < loop_n; i++) {
        //prediction_wall();
        //direct_branch_wall("ddd");
        //dwall();
        time_measured = measure_instance2(true, inputs[0]);
        average_measurement_time+=time_measured;
        //printf("%lx\n", time_measured);
        //time_measured -= measurement_cycles;
        log_result = log_2(time_measured);
        histogram[log_result]++;
    }
    /* Print to a file the results of the histogram. */
    FILE * out_file;
    DO_SYS2(out_file, NULL, fopen(output_path, "w"), "Error: cannot open file.");
    fprintf(out_file, "Average time: %f\n", average_measurement_time/((float)loop_n));
    for (int i = 0; i < REG_SIZE; i++) {
        fprintf(out_file, "%lu\n", histogram[i]);
    }
    free_strlist(num_inputs, inputs);
}


int main(int argc, const char** argv) {
    //override_ibpb();
    if(argc !=4) printf("Correct usage: ./oracle <inputs-file> <output-file> <iteration-count>\n");
    else measure_loop(argv[1], argv[2], atoi(argv[3]));
}

/* DRAFT:

Measure algorithm:
Input: number of loops, l.
    1. Set CPU to isolated core.
    2. Create array of ints, 64 cells. Initialize to zeros.
    3. In loop:
    3.1 Measure the end-start using measure_instance2.
    3.2 Calculate log and store in correct cell.
    4. Save histogram to file. (As excel?)

Remarks:
    1. We need a 64-cell array for the log values. Since the measurement is represented by 64 bits,
    we need only 64 cells. It's a histogram, so the size of the cells is defined by the number of loops.
    2. We need to efficiently measure the log.
    3. Need to compare Dan's measurement algorithm with ours.
    4. Must compile O1 (No optimizations).
TODO:
    1. Measurement algorithm.

*/