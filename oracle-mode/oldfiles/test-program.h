#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#define NUM_ITERATIONS 10000
typedef unsigned long int uint64_t;

char* generateRandomString() {
    static const char charset[] = "abc";
    char* randomString = (char*)malloc(sizeof(char) *NUM_ITERATIONS);
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        randomString[i] = charset[index];
    }
    randomString[NUM_ITERATIONS] = '\0';
    return randomString;
}

int direct_branch_wall(const char* arg) {
    //const char *in = argv[2];
    //All branches won't be taked if argv[1] is "ddd"
    char *check = generateRandomString();
    int sum=0;
    #pragma GCC unroll 10000
    for(int i=0; i < NUM_ITERATIONS; i++) {
        if(check[i]==arg[i%3])
            return 2;
    }
    free(check);
    return 1;
}