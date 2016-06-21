/* 
 * Authors: Felipe A. Louza, Simon Gog, Guilherme P. Telles
 * contact: louza@ic.unicamp.br
 * 21/06/2016
 */

/* 
 * This code is a modification of SACA-K algorithm by G. Nong, which can be
 * retrieved at: http://code.google.com/p/ge-nong/ 
 *
 * Our version of SACA-K, called gSACA-K, maintain the theoretical bounds of the
 * original algorithm to construct the generalized suffix array.
 *
 * New algorith gSACA-K+LCP extends gSAIS to also compute the LCP-array
 * 
 */

#ifndef GSACA_K_H
#define GSACA_K_H

#include <stdlib.h>
#include <stdio.h>

#include "../lib/utils.h"
#include "../lib/lcp_array.h"

int_t SACA_K(int_t *s, uint_t *SA,
  uint_t n, unsigned int K,
  uint_t m, int cs, int level);
  
/** @brief Computes the suffix array SA of T^cat in s[0..n-1]
 *
 *  @param s	input string
 *  @param SA 	suffix array 
 *  @param n	string length
 *  @param K	alphabet size
 *  @param cs 	size of a symbol in bytes
 *  @param level must be 0
 *  @param separator used between different strings in T^cat
 * 
 *  @return depth of the recursive calls.
 */
int_t gSACA_K(unsigned char *s, uint_t *SA,
  uint_t n, unsigned int K,
  int cs, int level, unsigned char separator);

/** @brief Computes the suffix and the LCP array T^cat in s[0..n-1]
 *  @param LCP 	LCP array 
 */
int_t gSACA_K_LCP(unsigned char *s, uint_t *SA, int_t *LCP,
  uint_t n, unsigned int K,
  int cs, int level, unsigned char separator);

#endif
