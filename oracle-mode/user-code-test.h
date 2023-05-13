
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned long int uint64_t;

void crash() {
    volatile int* p = 0;
    *p = 0;
}

int func(char *input_str) {
    char* fixed_str = "fixed string";
    int len = 12;
    for (int i = 0; i < len; i++) {
        if (fixed_str[i] != input_str[i]) {
            return 1;
        }

        __asm__("cpuid":::"memory");

        if (i == len - 1) {
            crash();
        }
    }

    return 0;
}

