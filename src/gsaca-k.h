/* 
 * Authors: Felipe A. Louza, Simon Gog, Guilherme P. Telles
 * contact: louza@ic.unicamp.br
 * 01/09/2015
 */

/* 
 * This code is a modification of SACA-K algorithm by G. Nong, which can be
 * retrieved at: http://code.google.com/p/ge-nong/ 
 *
 * Our version of SACA-K, called gSACA-K, maintain the theoretical bounds of the
 * original algorithm to construct the generalized suffix array.
 *
 */

#ifndef GSACA_K_H
#define GSACA_K_H

#include <stdlib.h>
#include <stdio.h>

#include "../lib/utils.h"

int_t SACA_K(int_t *s, uint_t *SA,
  uint_t n, unsigned int K,
  uint_t m, int cs, int level);

int_t gSACA_K(unsigned char *s, uint_t *SA,
  uint_t n, unsigned int K,
  uint_t m, int cs, int level, unsigned char separator);

#endif
