#ifndef SUFFIXARRAYH
#define SUFFIXARRAYH

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int suffix_array_print(int *SA, unsigned char *T, size_t len, int cs);

int suffix_array_check(int *SA, unsigned char *T, size_t len, int cs, unsigned char sentinel);

#endif
