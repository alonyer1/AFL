#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, const char** argv) {
    int sum=0;
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    #pragma GCC unroll 1000
    for(int i=0; i < 1000; i++) {
        if(num1+(i%2)==num2+(i%3))
            return 2;
    }
    return 1;
}