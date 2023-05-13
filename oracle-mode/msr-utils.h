typedef unsigned int u32;
typedef unsigned long long u64;

# define _ASM_EXTABLE_TYPE(from, to, type)			\
	" .pushsection \"__ex_table\",\"a\"\n"			\
	" .balign 4\n"						\
	" .long (" #from ") - .\n"				\
	" .long (" #to ") - .\n"				\
	" .long " #type " \n"			\
	" .popsection\n"
    
static inline void __wrmsr(unsigned int msr, u32 low, u32 high)
{
	asm volatile("1: wrmsr\n" "2:\n" _ASM_EXTABLE_TYPE(1b, 2b, 8) : : "c" (msr), "a"(low), "d" (high) : "memory");
}


static inline void wrmsrl(unsigned int msr, u64 val)
{
	__wrmsr(msr, (u32)(val & 0xffffffffULL), (u32)(val >> 32));
}