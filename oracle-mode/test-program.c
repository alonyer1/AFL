#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#define NUM_ITERATIONS 10
typedef unsigned long int uint64_t;

char* generateRandomString() {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char* randomString[NUM_ITERATIONS];
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        randomString[i] = charset[index];
    }
    randomString[NUM_ITERATIONS] = '\0';
    return randomString;
}

int main(int argc, const char** argv) {
    const char *in = argv[2];
    const char *check = generateRandomString();
    for(int i=0; i < 1000; i++) {
        if(check[i]==in[i])
                printf("test");

    }

}