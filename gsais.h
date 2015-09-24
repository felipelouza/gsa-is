// This is (a modification of) the sample code for the SA-IS algorithm presented in
// our article "Two Efficient Algorithms for Linear Suffix Array Construction"
// (co-authored with Sen Zhang and Wai Hong Chan),
// which can be retrieved at: http://code.google.com/p/ge-nong/

#ifndef GSAIS_H
#define GSAIS_H


#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <time.h>

#define tget(i) ( (t[(i)/8]&mask[(i)%8]) ? 1 : 0 )
#define tset(i, b) t[(i)/8]=(b) ? (mask[(i)%8]|t[(i)/8]) : ((~mask[(i)%8])&t[(i)/8])

#define isLMS(i) (i>0 && tget(i) && !tget(i-1))

/*
#define chr(i) (cs==sizeof(int)?((int*)s)[i]:((unsigned char *)s)[i])
#define false 0
#define true 1
*/

// find the suffix array SA of s[0..n-1] in {0..K-1}^n
// require s[n-1]=0 (the virtual sentinel!), n>=2
// level starts from 0
// returns the reduction depht
int SAIS(unsigned char *s, int *SA, int n, int K, int cs, int level);


// find the generalized suffix array GSA of s[0..n-1] in {0..K-1}^n
// require s[n-1]=0 (the virtual sentinel!), n>=2
// level starts from 0
// returns the reduction depht
int gSAIS(unsigned char *s, int *SA, int n, int K, int cs, int level, unsigned char separator);


#endif
