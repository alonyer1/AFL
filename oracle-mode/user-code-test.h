
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned long int uint64_t;
#define STR_LEN 12

int __attribute__((noinline)) func(char *input_str) {
    char* fixed_str = "fixed string";
#pragma GCC unroll 12
    for (int i = 0; i < STR_LEN; i++) {
        if (fixed_str[i] != input_str[i]) {
            return -1;
        }
        
        //asm volatile("cpuid":::"memory");
    }

    return 0;
}
int __attribute__((noinline)) func2(char *input_str) {
    char* fixed_str = "fixed string";
#pragma GCC unroll 12
    for (int i = 0; i < STR_LEN; i++) {
        if (fixed_str[i] != input_str[64*i]) {
            return -1;
        }
        
        //asm volatile("cpuid":::"memory");
    }

    return 0;
}

int __attribute__((noinline)) func3(char *input_str) {
    char* fixed_str = "fixed string";
#pragma GCC unroll 12
    for (int i = 0; i < STR_LEN; i++) {
        if (fixed_str[i] != input_str[64*i]) {
            continue;
        }
        return -1;
        //asm volatile("cpuid":::"memory");
    }

    return 0;
}
