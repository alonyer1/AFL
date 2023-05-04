#define _GNU_SOURCE
#define RUN_CODE

#ifdef RUN_CODE
#include "user-code-test.h"
#define USER_FUNCTION test_function
#endif

#include "oracle-run.h"
#include <unistd.h>
#include <sched.h>
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;

#define DO_SYS( call, error ) if((call)==-1) { perror(error); exit(-1); }
#define DO_SYS2( result, errval, call, error ) { result = (call); if((result)==(errval)) { perror(error); exit(-1); }}
#define ERR_AFFINITY "Error: cannot isolate core affinity."
#define ISOLATED_CORE 7
#define REG_SIZE 64

/* Efficient functions to use in measuring at the beginning and end. */
#define MEASURE_START( cycles_low, cycles_high ) asm volatile ("CPUID\n\t" "RDTSC\n\t" "mov %%edx, %0\n\t" "mov %%eax, %1\n\t" :\
        "=r"(cycles_high), "=r" (cycles_low):: "%rax", "%rdx", "%rbx", "%rcx", "memory")

#define MEASURE_END( cycles_low, cycles_high ) asm volatile ("RDTSCP\n\t" "mov %%edx, %0\n\t" "mov %%eax, %1\n\t" "CPUID\n\t" :\
        "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rdx", "%rbx", "%rcx", "memory")

/* Combine a variable containing lower 32 bits and higher 32 bits. */
#define JOIN64( high, low ) (((uint64_t)high << 32) | low)

/* Measure floor of log_2 efficiently. */
#define LOG_2( var, res ) asm ("BSRQ %1, %0" : "=r"(res) : "r"(var) : "memory")

/* Move process to isolated core. */
static inline void set_core(int core_num) {
    cpu_set_t core_mask;
    __CPU_ZERO_S (sizeof (cpu_set_t), &core_mask);
    __CPU_SET_S (ISOLATED_CORE, sizeof (cpu_set_t), &core_mask);
    DO_SYS(sched_setaffinity(0, sizeof(core_mask), &core_mask), ERR_AFFINITY)
}

/* Measure code once.*/
static inline uint64_t measure_instance2() {
    uint32_t cycles_low=0, cycles_high=0, cycles_low1=0, cycles_high1=0;
    MEASURE_START(cycles_low, cycles_high);
#ifdef RUN_CODE
    //USER_FUNCTION();
    printf("idk\n");
#endif
    MEASURE_END(cycles_low1, cycles_high1);
    uint64_t start = JOIN64(cycles_high, cycles_low);
    uint64_t end = JOIN64(cycles_high1, cycles_low1);
    return end-start;
}

void measure_loop(const char* output_path, int loop_n) {
    set_core(ISOLATED_CORE);
    long unsigned int histogram[REG_SIZE] = {0};
    uint64_t log_result=0;
    for(int i=0; i < loop_n; i++) {
        LOG_2(measure_instance2, log_result);
        histogram[log_result]++;
    }
    FILE * out_file;
    DO_SYS2(out_file, NULL, fopen(output_path, "w"), "Error: cannot open file.");
    for (int i = 0; i < REG_SIZE; i++) {
        fprintf(out_file, "%d: %lu\n", i, histogram[i]);
    }

}

int main(int argc, const char** argv) {
    uint64_t time = measure_instance2();
    printf("Measurement: %lx\n", time);
    uint64_t logop=127, logres=0;
    LOG_2(logop, logres);
    printf("Log2 of %lu is %lu.\n", logop, logres);

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