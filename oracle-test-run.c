#define _GNU_SOURCE
#include "oracle-run.h"
#include <unistd.h>
#include <sched.h>
typedef unsigned long int uint64_t;
typedef unsigned int uint32_t;
uint64_t measure_instance2() {
    cpu_set_t core_mask;
    __CPU_ZERO_S (sizeof (cpu_set_t), &core_mask);
    //CPU_SET(0, &core_mask);
    __CPU_SET_S (7, sizeof (cpu_set_t), &core_mask);
    sched_setaffinity(0, sizeof(core_mask), &core_mask);
    //printf("Pid: %d\n", getpid());

    uint32_t cycles_low=0, cycles_high=0, cycles_low1=0, cycles_high1=0;
    //printf("%lu\n%lu\n%lu\n%lu\n", cycles_high, cycles_low, cycles_high1, cycles_low1);
    asm volatile ("CPUID\n\t" "RDTSC\n\t" "mov %%edx, %0\n\t" "mov %%eax, %1\n\t" :
                "=r"(cycles_high), "=r" (cycles_low):: "%rax", "%rdx", "%rbx", "%rcx", "memory");
    //code();
    for(int i=0; i<100000; i++)
        i = i;
    asm volatile ("RDTSCP\n\t" "mov %%edx, %0\n\t" "mov %%eax, %1\n\t" "CPUID\n\t" :
                "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rdx", "%rbx", "%rcx", "memory");
    printf("High: %x\nLow: %x\nHigh, end:%x\nLow, end:%x\n\n", cycles_high, cycles_low, cycles_high1, cycles_low1);
    uint64_t start = ((uint64_t)cycles_high << 32) | cycles_low;
    uint64_t end = ((uint64_t) cycles_high1 << 32) | cycles_low1;
    printf("Start: %lx\nEnd: %lx\n", start,end);
    return end-start;
}
int main(int argc, const char** argv) {
    //printf("%d",run_binary("./test.out"));
    printf("Measurement: %lx\n", measure_instance2());
    //printf("%llx\n", measure_instance2());
    //printf("%llx\n", measure_instance2());
}