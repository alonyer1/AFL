//##############################################################################
//   FILE: getcycles.h
// AUTHOR: Dan Tsafrir 
//   NOTE: Use do_pin on an SMP/multicore whenever possible.
//##############################################################################
#ifndef GETCYCLES_H__
#define GETCYCLES_H__
#include <stdint.h>


//------------------------------------------------------------------------------
#if defined(__x86_64__) /*http://www.gelato.unsw.edu.au/IA64wiki/rdtscOnAmd64*/
//------------------------------------------------------------------------------
inline uint64_t get_cycles() {
    unsigned int a, d;
    asm volatile("rdtsc" : "=a" (a), "=d" (d));
    return ( ((unsigned long)a) | (((unsigned long)d)<<32) );
}


//------------------------------------------------------------------------------
#elif defined(__i386__)    || \
      defined(__i486__)    || \
      defined(__pentium__) || \
      defined(__i686__)
//------------------------------------------------------------------------------
inline uint64_t get_cycles() {
    uint64_t ret;
    asm volatile("rdtsc" : "=A" (ret));
    return ret;
}

//------------------------------------------------------------------------------
#elif defined(__powerpc__)
//------------------------------------------------------------------------------
#if 0 /* 32bit version */
inline uint64_t get_cycles() {
    uint64_t ret;
    __asm__ __volatile__ ("mftb %0": "=&r" (ret) : /* inputs */);
    return ret;
}
#else /* generalize to 64bit */
inline uint64_t get_cycles() {
    unsigned int highB, highA, low;
    do {
	//asm volatile( "sync" );
	asm volatile( "mftbu %0" : "=r"(highB) );
	asm volatile( "mftb  %0" : "=r"(low)    );
	asm volatile( "mftbu %0" : "=r"(highA) );
    } while (highB != highA);
    return ((uint64_t)highA) << 32 | (uint64_t)low;
}
#endif


//------------------------------------------------------------------------------
#elif defined(__ia64__)
//------------------------------------------------------------------------------
inline uint64_t get_cycles() {
    uint64_t ret;
    asm volatile ( "mov     %0 = ar.itc" : "=r" (ret) );
    return ret;
}


//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
#  error no get_cycles implementation
#endif


#endif /*GETCYCLES_H__*/
//##############################################################################
//                                   EOF
//##############################################################################
