//#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
typedef void (*code_ptr)();
typedef unsigned long long u64;
typedef unsigned int u32;
static inline size_t get_file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t res = ftell(file);
    rewind(file);
    return res;
}

u64 measure_instance(code_ptr code) {

    u64 cycles_low, cycles_high, cycles_low1, cycles_high1;
    /* Must somehow prevent preemptions.
    Preempt_disable() on kernel space.
    Then disabling hard interrupts with raw_local_irq_save().
    In asm, '=' means write-only and replace. 'r' register operand.
    To run the executable, we must use fopen.
    File must be compiled as position-indepentent executable to be loaded into memory.
    */

    asm volatile ("CPUID\n\t" "RDTSC\n\t" "CPUID\n\t" "mov %0, %%rdx\n\t"
                "mov %1, %%rax\n\t":
                "=rdx" (cycles_high), "=r" (cycles_low):: "%rax", "%rdx", "%rbx", "%rcx");
    //code();
    printf("code\n");
    asm volatile ("CPUID\n\t" "RDTSC\n\t" "CPUID\n\t" "mov %0, %%rdx\n\t"
                "mov %1, %%rax\n\t":
                "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rdx", "%rbx", "%rcx");
    u64 start = (cycles_high << 32) + cycles_low;
    u64 end = (cycles_high1 << 32) + cycles_low1;
    return end-start;
}

u64 run_binary(char* fname) {
    FILE* file = fopen(fname, "rb");
    if(file == NULL) exit(EXIT_FAILURE); //Insert error here
    size_t file_size = get_file_size(file);
    //char* buffer = (char*) mmap(NULL, file_size, PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    char* buffer = (char*) malloc(file_size);
    if(buffer == MAP_FAILED) exit(EXIT_FAILURE);
    for(int i = 0; i < file_size; i++) {
       fread(buffer+i, 1, 1, file);
    }
    fclose(file);
    u64 result = measure_instance((code_ptr)buffer);
    //if(munmap(buffer,file_size)==-1) exit(EXIT_FAILURE);
    free(buffer);
    return result;
}
