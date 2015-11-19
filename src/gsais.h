// This is (a modification of) SA-IS algorithm, which can be retrieved at:
// http://code.google.com/p/ge-nong/ 
// Our version of SAIS, called gSAIS, maintain the theoretical bounds of the
// original algorithm to construct the generalized suffix array.

#ifndef GSAIS_H
#define GSAIS_H

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#include "../lib/utils.h"

#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])

#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

// find the suffix array SA of s[0..n-1] in {0..K-1}^n
// require s[n-1]=0 (the virtual sentinel!), n>=2
// level starts from 0
// returns the reduction depht
int_t SAIS(int_t *s, int_t *SA, int_t n, int_t K, int cs, int level);


// find the (generalized) suffix array GSA of s[0..n-1] in {0..K-1}^n
// require s[n-1]=0 (the virtual sentinel!), n>=2
// level starts from 0
// returns the reduction depht
int_t gSAIS(unsigned char *s, int_t *SA, int_t n, int_t K, int cs, int level, unsigned char separator);


#endif
