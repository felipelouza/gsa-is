#ifndef DAH
#define DAH

#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "utils.h"
#include "file.h"

#ifndef DEBUG
        #define DEBUG 0
#endif

int document_array_LF(unsigned char* T, int_t* SA, int_da* DA, uint_t n, unsigned int SIGMA, int cs, unsigned char separator, uint_t k);
int document_array_LF_int(int_text* T, int_t* SA, int_da* DA, uint_t n, unsigned int SIGMA, int cs, unsigned char separator, uint_t k);

int document_array_ISA(unsigned char* T, int_t* SA, int_t* DA, uint_t n, unsigned int SIGMA, int cs, unsigned char separator, uint_t k);

int document_array_9n(unsigned char* T, int_t* SA, int_da* DA, uint_t n, unsigned int SIGMA, int cs, unsigned char separator, uint_t k);
/**/

int document_array_check(unsigned char *T, int_t *SA, int_da *DA, uint_t n, int cs, unsigned char separator, uint_t k);

int document_array_check_int(int_text *T, int_t *SA, int_da *DA, uint_t n, int cs, uint_t k);

int document_array_print(unsigned char *T, int_t *SA, int_da *DA, size_t n, int cs);
int document_array_write(int_da *DA, int_t n, char* c_file, const char* ext);
int_t document_array_read(int_da** DA, char* c_file, const char* ext);

/**/

#endif
