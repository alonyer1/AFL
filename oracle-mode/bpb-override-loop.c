#include <stdlib.h> 
#include <stdbool.h>
#define LOOP_COUNT 10000

void btb_override() {
    for(int i=0; i < LOOP_COUNT; i++) {
        bool random_boolean = rand() % 2;
        asm volatile(
            "test %0, 1\n" 
            "je .direct_label_" __STRING(i) "\n"
            "nop\n"
            ".direct_label_" __STRING(i) ":\n"
            "jmp *indirect_label_" __STRING(i) "\n"
            "nop\n"
            "indirect_label_" __STRING(i) ":\n"
        : : "r" (random_boolean));
    }
}

void cache_override() {

}