as dwall.s -g -o dwall.o
as user-code-test.s -g -o user-code-test.o
gcc -g -c -Werror -O1 oracle-test-run.c -o oracle1.o
gcc -g -static oracle1.o user-code-test.o dwall.o -o oracle