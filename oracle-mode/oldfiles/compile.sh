gcc -c -O1 oracle-test-run.c -o oracle1.o
gcc -static oracle1.o dwall.o -o oracleRealWallMulti