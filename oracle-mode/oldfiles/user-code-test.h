
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned long int uint64_t;
#define STR_LEN 12
//#pragma GCC optimize ("unroll-loops")
/*void crash() {
    volatile int* p = 0;
    *p = 0;
}*/

int __attribute__((noinline)) func(char *input_str) {
    char* fixed_str = "fixed string";
#pragma GCC unroll 12
    for (int i = 0; i < STR_LEN; i++) {
        if (fixed_str[i] != input_str[i]) {
            return -1;
        }
        __asm__("cpuid":::"memory");
        /*if (i == STR_LEN - 1) {
            break;
        }*/
    }

    return 0;
}
