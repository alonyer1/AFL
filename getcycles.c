#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/syscall.h> /* syscall */
#include <unistd.h>      /* syscall */
#define __USE_GNU        /* CPU_ZERO etc., within shced.h */
#include <sched.h>       /* sched_setaffinity */
#include <errno.h>       /* perror */
#include "getcycles.h"
#include "user-code-test.h"
#define N 100000
int arr_tsc[N];
struct timespec arr_clk[N];
#define HZ_COM                                                                \
    "perl -e '@x=`cat /proc/cpuinfo`;@x=grep(/MHz/,@x);@x[0]=~m/:\\s(\\S+)/;" \
    "print $1'"

//------------------------------------------------------------------------------
// pin process to a core i
//------------------------------------------------------------------------------
void do_pin(int i)
{
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(7, &cpuset);
    if (sched_setaffinity(i, sizeof(cpuset), &cpuset) == -1)
    {
        perror("sched_setaffinity");
        exit(1);
    }
}

//------------------------------------------------------------------------------
// speed of cpu (this machine) in MHz
//------------------------------------------------------------------------------
double get_machine_mhz()
{
    double mhz;
    FILE *f = popen(HZ_COM, "r");
    fscanf(f, "%lf", &mhz);
    return mhz;
}

//------------------------------------------------------------------------------
// measure
//------------------------------------------------------------------------------
int main()
{

    int i;
    double sum_tsc, sum_clk, sum_sys, diff, mhz, ghz;
    struct timespec hi, lo;

    do_pin(0);

    //
    // tsc
    //
    memset(arr_tsc, '\0', sizeof(arr_tsc)); // alloc

    for (i = 0; i < N; i++)
        arr_tsc[i] = get_cycles();

    sum_tsc = 0;
    for (i = 1; i < N; i++)
        sum_tsc += (arr_tsc[i] - arr_tsc[i - 1]);

    //
    // clk
    //
    memset(arr_clk, '\0', sizeof(arr_clk)); // alloc

    for (i = 0; i < N; i++)
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, arr_clk + i);

    sum_clk = 0;

    for (i = 1; i < N; i++)
    {

        lo = arr_clk[i - 1];
        hi = arr_clk[i];

        if (lo.tv_sec == hi.tv_sec)
        {
            diff = hi.tv_nsec - lo.tv_nsec;
        }
        else
        {
            diff = 1000000000.0L * (hi.tv_sec - lo.tv_sec);
            diff += 1000000000.0L + hi.tv_nsec - lo.tv_nsec;
        }
        sum_clk += diff;
    }

    //
    // sys
    //
    {
        uint64_t before, after;
        before = get_cycles();
        for (i = 0; i < N; i++)
            func("abcdefg");
        after = get_cycles();
        sum_sys = after - before;
    }

    //
    // results
    //
    mhz = get_machine_mhz();
    ghz = mhz / 1000.0;
    printf("# ghz=%lf\n", ghz);
    printf("tsc granularity: %f\n", (sum_tsc / N) / ghz);
    printf("clk granularity: %f\n", (sum_clk / N));
    printf("sys granularity: %f\n", (sum_sys / N));

    return 0;
}
