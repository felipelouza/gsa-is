/* 
 * Authors: Felipe A. Louza, Simon Gog, Guilherme P. Telles
 * contact: louza@ic.unicamp.br
 * 07/06/2016
 */

/* 
 * This code is a modification of SA-IS algorithm by G. Nong, which can be
 * retrieved at: http://code.google.com/p/ge-nong/ 
 *
 * Our version of SA-IS, called gSAIS, maintain the theoretical bounds of the
 * original algorithm to construct the generalized suffix array.
 * 
 * News:
 * - gSA-IS+LCP extends gSAIS to also compute the LCP-array
 * - gSA-IS+DA extends gSAIS to also compute the document-array
 */

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

int_t SAIS(int_t *s, int_t *SA, int_t n, int_t K, int cs, int level);

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
int_t gSAIS(unsigned char *s, int_t *SA, int_t n, int_t K, int cs, int level, unsigned char separator);

/** @brief Computes the suffix and the LCP array T^cat in s[0..n-1]
 *  @param LCP 	LCP array 
 */
int_t gSAIS_LCP(unsigned char *s, int_t *SA, int_t *LCP, int_t n, int_t K, int cs, int level, unsigned char separator);

/** @brief Computes the suffix and the Document array T^cat in s[0..n-1]
 *  @param DA 	DA array 
 */
int_t gSAIS_DA(unsigned char *s, int_t *SA, int_t *DA, int_t n, int_t K, int cs, int level, unsigned char separator);


#endif
