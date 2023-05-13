gcc -c -O0 -funroll-loops bpb-override-loop.c -o bpb.o
gcc -c oracle-test-run.c -o oracle.o
gcc -o oracle bpb.o oracle.o