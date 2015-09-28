#ifndef SUFFIXARRAYH
#define SUFFIXARRAYH

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "utils.h"

int_t suffix_array_print(int_t *SA, unsigned char *T, size_t len, int cs);
int_t suffix_array_check(int_t *SA, unsigned char *T, size_t len, int cs, unsigned char sentinel);

#endif
