as dwall.s -g -o dwall.o
gcc -g -c -Werror -O1 oracle-test-run.c -o oracle1.o
gcc -g -static oracle1.o dwall.o -o oracle