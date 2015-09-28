#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#ifndef UCHAR_SIZE
#define UCHAR_SIZE 256
#endif

#define END_MARKER '$'

#define m64 1

#if m64
	typedef int64_t  int_t;
	typedef uint64_t uint_t;
	#define PRIdN	 PRId64
#else
	typedef int32_t  int_t;
	typedef uint32_t uint_t;
	#define PRIdN	 PRId32
#endif

typedef uint32_t int_text;


/**********************************************************************/

#define swap(a,b) do { typeof(a) aux_a_b = (a); (a) = (b); (b) = aux_a_b; } while (0)

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

double time_stop(time_t t_time, clock_t c_clock);

void die(const char* where);
void dies(const char* where, char* format, ...);

int_t print_int(int_t* A, int_t n);
int_t print_char(char* A, int_t n);
int_t min_range(int_t* A, int_t l, int_t r);

/**********************************************************************/

#endif
