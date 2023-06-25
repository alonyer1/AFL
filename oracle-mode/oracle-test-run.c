#define _GNU_SOURCE
#define RUN_CODE

#ifdef RUN_CODE

// #define USER_FUNCTION func2
#endif
#include <stdbool.h>
// #include "../oracle-run.h"
#include <unistd.h>
#include <sched.h>
#include "msr-utils2.h"
#include <string.h>
#define USER_FUNCTION (func4)

/* External functions. */
extern void dwall();
extern int func(char *input_str);
extern int func2(char *input_str);
extern int func3(char *input_str);
extern int func4(char *input_str);
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;
#define FIRST_ITERATIONS (100)
#define DO_SYS(call, error) \
    if ((call) == -1)       \
    {                       \
        perror(error);      \
        exit(-1);           \
    }
#define ERR_AFFINITY "Error: cannot isolate core affinity."
#define ISOLATED_CORE (3)
#define REG_SIZE (64)
#define CACHELINE_SIZE (512)
#define STRLEN (12)
#define WRITE ("w")
#define ARR_SIZE 256
/* Efficient functions to use in measuring at the beginning and end. */

// extern void btb_override();

int line_index[STRLEN] = {0, 1, 3, 6, 7, 10, 14, 20, 22, 28, 31, 47};
#define CACHESIZE 4096
#define BIGLEN (STRLEN *CACHELINE_SIZE)

static inline uint64_t measure_start()
{
    uint32_t cycles_low = 0, cycles_high = 0;
    asm volatile("CPUID\n\t"
                 "RDTSC\n\t"
                 : "=a"(cycles_low), "=d"(cycles_high)::"%rbx", "memory");
    return (((uint64_t)cycles_high << 32) | cycles_low);
}

static inline uint64_t measure_end()
{
    uint32_t cycles_low = 0, cycles_high = 0, aux = 0;
    asm volatile("RDTSCP\n\t"
                 : "=a"(cycles_low), "=d"(cycles_high), "=c"(aux)::"%rbx", "memory");
    return (((uint64_t)cycles_high << 32) | cycles_low);
}

inline uint64_t dan_get_cycles()
{
    unsigned int a, d;
    asm volatile("rdtsc"
                 : "=a"(a), "=d"(d)::"memory");
    return (((unsigned long)a) | (((unsigned long)d) << 32));
}

/* Measure floor of log_2 efficiently. */
static inline uint64_t log_2(uint64_t var)
{
    uint64_t res = 0;
    asm("BSRQ %1, %0"
        : "=r"(res)
        : "r"(var));
    return res;
}

/* Move process to isolated core. */
static inline void set_core(int core_num)
{
    cpu_set_t core_mask;
    __CPU_ZERO_S(sizeof(cpu_set_t), &core_mask);
    __CPU_SET_S(ISOLATED_CORE, sizeof(cpu_set_t), &core_mask);
    DO_SYS(sched_setaffinity(0, sizeof(core_mask), &core_mask), ERR_AFFINITY)
}

/* Measure code once. If argument is true, measure a function provided by macro.*/
static inline uint64_t run_and_measure(char *arg)
{
    uint64_t start = measure_start();
    USER_FUNCTION(arg);
    uint64_t end = measure_end();
    return end - start;
}
void free_list(int length, char **list)
{
    for (int i = 0; i < length; i++)
        free(list[i]);
    free(list);
}
char **get_lines(const char *input_file_path, int *line_count)
{
    FILE *file = fopen(input_file_path, "r");
    if (file == NULL)
    {
        perror("Failed to open input file.\n");
        exit(-1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t have_read = 0;
    // Count the number of lines in the file
    *line_count = 0;
    while ((have_read = getline(&line, &len, file)) != -1)
    {
        (*line_count)++;
    }
    rewind(file);
    // Allocate an array of string pointers
    char **list = (char **)valloc(sizeof(char *) * (*line_count));
    if (list == NULL)
    {
        perror("Failed to allocated.\n");
        exit(-1);
    }

    // Read the file again, line by line
    for (int i = 0; ((have_read = getline(&line, &len, file)) != -1); i++)
    {
        // Remove newline character, if present
        if (line[have_read - 1] == '\n')
        {
            line[have_read - 1] = '\0';
            have_read--;
        }

        // Allocate memory for the line in the list
        list[i] = (char *)valloc(have_read + 1);
        if (list[i] == NULL)
        {
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
void run_loop_histogram(const char *input_file_path, const char *output_file_path, int loop_n)
{
    // Isolate core.
    set_core(ISOLATED_CORE);
    long unsigned int histogram[REG_SIZE] = {0};
    // Create an array of inputs from file, every line corresponds to different input.
    int num_inputs = 0;
    char **input_file_lines = get_lines(input_file_path, &num_inputs);
    /* loop_n iterations:
    1. "dwall" resets the branch predictors.
    2. run_and_measure measures func from start to finish.
    3. highest set bit of the result is stored in histogram. */
    uint64_t log_result = 0, cycles_measured = 0;
    uint64_t average_cycles = 0;
    for (int i = 0; i < loop_n; i++)
    {
        cycles_measured = run_and_measure(input_file_lines[0]);
        average_cycles += cycles_measured;
        log_result = log_2(cycles_measured);
        histogram[log_result]++;
    }
    /* Print to a file the results of the histogram. */
    FILE *out_file;
    out_file = fopen(output_file_path, "w");
    if (out_file == NULL)
    {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_cycles / ((float)loop_n));
    for (int i = 0; i < REG_SIZE; i++)
    {
        fprintf(out_file, "%lu\n", histogram[i]);
    }
    fclose(out_file);
    free_list(num_inputs, input_file_lines);
}
void run_loop(const char *input_file_path, const char *output_file_path, int loop_n)
{
    // Isolate core.
    set_core(ISOLATED_CORE);
    uint64_t *results = (uint64_t *)valloc(loop_n * sizeof(uint64_t));
    if (results == NULL)
    {
        perror("Failed to allocate.\n");
        exit(-1);
    }
    // Create an array of inputs from file. We only use the first line on a file, input_file_lines[0].
    int num_inputs = 0;
    char **input_file_lines = get_lines(input_file_path, &num_inputs);
    uint64_t cycles_measured = 0;
    uint64_t average_cycles = 0;
    /* loop_n iterations:
    1. use function "dwall" to reset branch predictors.
    2. run_and_measure calls func and measures cycles from before to after call.
    3. result is stored in the array.
    */
    for (int i = 0; i < loop_n; i++)
    {
        dwall(); // This function is just a series of jumps that aren't taken
        cycles_measured = run_and_measure(input_file_lines[0]);
        average_cycles += cycles_measured;
        results[i] = cycles_measured;
    }
    /* Print results to file. */
    FILE *out_file;
    out_file = fopen(output_file_path, "w");
    if (out_file == NULL)
    {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_cycles / ((float)loop_n));
    for (int i = 0; i < loop_n; i++)
    {
        fprintf(out_file, "%lu\n", results[i]);
    }
    fclose(out_file);
    free_list(num_inputs, input_file_lines);
    free(results);
}

inline void clflush(volatile void *address)
{
    asm volatile("clflush (%0)\n\t" ::"r"(address)
                 : "memory");
}

void run_loop_cache(const char *input_file_path, const char *output_file_path, int loop_n)
{
    // Isolate core.
    set_core(ISOLATED_CORE);
    // Disable cache prefetching.
    disable_prefetching();

    uint64_t *results = (uint64_t *)valloc(loop_n * sizeof(uint64_t));
    if (results == NULL)
    {
        perror("Failed to allocate.\n");
        exit(-1);
    }

    // Create an array of inputs from file. We only use the first line on a file, input_file_lines[0].
    // We use that line to create "big_input" a string where ever cache line represents one char from input_file_lines[0].
    int num_inputs = 0;
    char **input_file_lines = get_lines(input_file_path, &num_inputs);
    uint64_t cycles_measured = 0;
    uint64_t average_cycles = 0;
    char *big_input = (char *)valloc(BIGLEN);
    if (!big_input)
    {
        perror("Failed to allocate.\n");
        exit(-1);
    }
    for (int i = 0; i < BIGLEN; i++)
        big_input[i] = 'a';
    for (int i = 0; i < STRLEN; i++)
    {
        big_input[i * CACHELINE_SIZE] = input_file_lines[0][i];
    }
    /* loop_n iterations:
    1. flush the cache lines.
    2. run_and_measure calls func2 and measures cycles from start to finish.
    3. result is stored in the array.
    */
    for (int i = 0; i < loop_n; i++)
    {
        for (int j = 0; j < STRLEN; j++)
            clflush(big_input + (j * CACHELINE_SIZE));
        asm volatile("mfence" ::
                         : "memory");
        cycles_measured = run_and_measure(big_input);
        average_cycles += cycles_measured;
        results[i] = cycles_measured;
    }
    /* Print all results to a file. */
    FILE *out_file;
    out_file = fopen(output_file_path, WRITE);
    if (out_file == NULL)
    {
        perror("Cannot open file.\n");
        exit(-1);
    }
    fprintf(out_file, "Average time: %f\n", average_cycles / ((float)loop_n));
    for (int i = 0; i < loop_n; i++)
    {
        fprintf(out_file, "%lu\n", results[i]);
    }
    // Free structures.
    fclose(out_file);
    free_list(num_inputs, input_file_lines);
    free(big_input);
    free(results);
}

int prime(uint8_t* array) {
	int i, junk = 0;
    asm volatile ("mfence\t\n"
				"lfence\t\n" ::: "memory");
	for (i = 0; i < ARR_SIZE; i++)
		junk += array[i * CACHELINE_SIZE];
    asm volatile ("mfence\t\n"
				"lfence\t\n" ::: "memory");
	return junk;
}

unsigned long probe_one(volatile uint8_t* adrs) {
	volatile unsigned long time;
	asm volatile ("mfence\t\n"
				"lfence\t\n"
				"rdtsc\t\n"
				"lfence\t\n"
				"movl %%eax, %%esi\t\n"
				"movl (%1), %%eax\t\n"
				"lfence\t\n"
				"rdtsc\t\n"
				"subl %%esi, %%eax\t\n"
				"clflush 0(%1)\t\n"
				: "=a"(time)
				: "c"(adrs)
				: "%esi", "%edx", "memory");
	return time;
}

void probe(uint8_t* array, uint64_t * results) {
	int i, mix_i;
	volatile uint8_t *addr;
	for(i=0; i<ARR_SIZE; i++) {
		mix_i = ((i * 167) + 13) % ARR_SIZE;
        //printf("mix_i:%d\n", mix_i);
		addr = array + (mix_i*CACHELINE_SIZE);
		results[mix_i] = probe_one(addr);
	}
}

void run_prime_probe(const char *input_file_path, const char *output_file_path)
{
    // Isolate core.
    set_core(ISOLATED_CORE);
    // Disable cache prefetching.
    //disable_prefetching();
    int num_inputs = 0;
    char **input_file_lines = get_lines(input_file_path, &num_inputs);

    char *big_input = (char *)valloc(ARR_SIZE * CACHELINE_SIZE);
    if (!big_input)
    {
        perror("Failed to allocate.\n");
        exit(-1);
    }
    uint64_t *results = (uint64_t *)valloc(sizeof(uint64_t) * ARR_SIZE);
    if (results == NULL)
    {
        perror("Failed to allocate.\n");
        exit(-1);
    }
    for (int i = 0; i < BIGLEN; i++)
        big_input[i] = 'a';
    for (int i = 0; i < STRLEN; i++)
    {
        big_input[i * CACHELINE_SIZE] = input_file_lines[0][i];
    }
    for (int j = 0; j < ARR_SIZE; j++) clflush(big_input + (j * CACHELINE_SIZE));
    //prime(big_input);
    USER_FUNCTION(big_input);
    probe(big_input, results);
    FILE *out_file;
    out_file = fopen(output_file_path, WRITE);
    if (out_file == NULL)
    {
        perror("Cannot open file.\n");
        exit(-1);
    }
    for (int i = 0; i < ARR_SIZE; i++)
    {
        fprintf(out_file, "%lu\n", results[i]);
    }
    // Free structures.
    fclose(out_file);
    free_list(num_inputs, input_file_lines);
    free(big_input);
    free(results);
}

int main(int argc, const char **argv)
{
    if (argc != 4)
        printf("Correct usage: ./oracle <inputs-file> <output-file> <iteration-count>\n");
    else
        //run_loop_cache(argv[1], argv[2], atoi(argv[3]));
        run_prime_probe(argv[1], argv[2]);
}