// Author: Ge Nong,  Email: issng@mail.sysu.edu.cn
// Department of Computer Science, Sun Yat-sen University, 
// Guangzhou, China
// Date: December 24, 2012
//
// This is the demo source code for the algorithm SACA-K presented in this article:
// G. Nong, Practical Linear-Time O(1)-Workspace Suffix Sorting for Constant Alphabets, 
// ACM Transactions on Information Systems, Scheduled to Appear in July 2013.
// A draft for this article can be retrieved from http://code.google.com/p/ge-nong/.

#ifndef GSACA_K_H
#define GSACA_K_H

#include <stdlib.h>
#include <stdio.h>

#include "lib/utils.h"

/*
// set only the highest bit as 1, i.e. 1000...
const unsigned int EMPTY=((unsigned int)1)<<(sizeof(unsigned int)*8-1);
*/

// get s[i] at a certain level
//#define chr(i) ((level==0)?((unsigned char *)s)[i]:((int *)s)[i])

int_t SACA_K(int_t *s, uint_t *SA,
  uint_t n, unsigned int K,
  uint_t m, int cs, int level);

int_t gSACA_K(unsigned char *s, uint_t *SA,
  uint_t n, unsigned int K,
  uint_t m, int cs, int level, unsigned char separator);

#endif
