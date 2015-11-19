/*
 * Induced Suffix Sorting for String Collections
 *
 * Authors: Felipe A. Louza, Simon Gog, Guilherme P. Telles
 * contact: louza@ic.unicamp.br
 * 01/09/2015
 *
 */

#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "lib/utils.h"
#include "lib/file.h"
#include "lib/suffix_array.h"
#include "external/malloc_count/malloc_count.h"
#include "gsais.h"
#include "gsaca-k.h"

#define DEBUG 0

/*******************************************************************/
int_t* cat_int(unsigned char** R, int k, int_t *n){

	(*n)++; //add 0 at the end

	int_t i, j;
	int_t l=0;
	int_t *str_int = (int_t*) malloc((*n)*sizeof(int_t));

	for(i=0; i<k; i++){
		int_t m = strlen((char*)R[i]);
		for(j=0; j<m; j++)
			str_int[l++] = R[i][j]+(k+1);
		str_int[l++] = i+1; //add $_i as separator

	}
	
	str_int[l]=0;

return str_int;
}
/*******************************************************************/
unsigned char* cat_char(unsigned char** R, int k, int_t *n){

	(*n)++; //add 0 at the end

	int_t i, j;
	int_t l=0;
	unsigned char *str = (unsigned char*) malloc((*n)*sizeof(unsigned char));

	for(i=0; i<k; i++){
		int_t m = strlen((char*)R[i]);
		for(j=0; j<m; j++){
			str[l++] = R[i][j]+1;
		}
		str[l++] = 1; //add 1 as separator
	}

	str[l]=0;

return str;
}

/*******************************************************************/

int main(int argc, char** argv){

int VALIDATE=0, MODE=0, OUTPUT=0;

	if(argc!=7){
		dies(__func__,"argc!=4");
	}

	unsigned char **R;
	int_t i, n=0;
	int   k;

	char* c_dir = argv[1];
	char* c_file = argv[2];

	sscanf(argv[3], "%d", &k);
	sscanf(argv[4], "%u", &MODE);
	sscanf(argv[5], "%u", &VALIDATE);
	sscanf(argv[6], "%u", &OUTPUT);

	file_chdir(c_dir);

	//disk access
	R = (unsigned char**) file_load_multiple(c_file, k, &n);
	if(!R){
		fprintf(stderr, "Error: less than %d strings in %s\n", k, c_file);
		return 0;
	}

	printf("K = %" PRId32 "\n", k);
	printf("N = %" PRIdN "\n", n+1);
	printf("sizeof(int) = %zu bytes\n", sizeof(int_t));

	unsigned char *str = NULL;
	int_t  *str_int = NULL;
	
	//concatenate strings
	if(MODE==1 || MODE==2){//sais or saca-k (int)	
		str_int = cat_int(R, k, &n);
		
		#if DEBUG
		int_t i=0;
		for(;i<n; i++)
			 printf("%" PRIdN ") %" PRIdN "\n", i, str_int[i]);
		printf("\n");
		#endif
	}
	else{ // sais, saca-k, gsais, gsaca-k (char)
		str = cat_char(R, k, &n);
		#if DEBUG
		int_t i=0;
		for(;i<n; i++)
			 printf("%" PRIdN ") %d\n", i, str[i]);
		printf("\n");
		#endif
	}

	#if DEBUG
		printf("R:\n");
		for(i=0; i<k; i++)
			printf("%" PRIdN ") %s (%zu)\n", i, R[i], strlen((char*)R[i]));
	#endif

	//free memory
	for(i=0; i<k; i++)
		free(R[i]);
	free(R);

	//sorted array
	int_t *SA = (int_t*) malloc(n*sizeof(int_t));
	int_t depth=0;

	time_t t_start = time(NULL);
	clock_t c_start =  clock();

	switch(MODE){
		case 1: printf("## SAIS (int) ##\n");
			depth = SAIS((int_t*)str_int, SA, n, 256+k, sizeof(int_t), 0);
			break;

		case 2: printf("## SACA_K (int) ##\n"); 
			depth = SACA_K((int_t*)str_int, (uint_t*)SA, n, 256+k, n, sizeof(int_t), 0);
			break;
		
		case 3: printf("## SAIS (char) ##\n");
			depth = SAIS((int_t*)str, SA, n, 256, sizeof(char), 0);
			break;

		case 4: printf("## SACA_K (char) ##\n"); 
			depth = SACA_K((int_t*)str, (uint_t*)SA, n, 256, n, sizeof(char), 0);
			break;
	
		case 5: printf("## gSAIS ##\n"); 
			depth = gSAIS((unsigned char*)str, SA, n, 256, sizeof(char), 0, 1);//separator=1
			break;

 		case 6: printf("## gSACA_K ##\n"); 
			depth = gSACA_K((unsigned char*)str, (uint_t*)SA, n, 256, n, sizeof(char), 0, 1);
			break;
		
		default: break;
	}

	printf("total:\n");
	time_stop(t_start, c_start);

	// validate	
	if(VALIDATE){
		if(MODE==1 || MODE==2){//sais or saca-k	
	        	if(!suffix_array_check(SA, (unsigned char*)str_int, n, sizeof(int_t), 0)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}
		else if(MODE==3 || MODE==4){
	        	if(!suffix_array_check(SA, (unsigned char*)str, n, sizeof(char), 0)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}
		else if(MODE==5 || MODE==6){
	        	if(!suffix_array_check(SA, (unsigned char*)str, n, sizeof(char), 1)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}
	}
	else printf("depth = %" PRIdN "\n", depth);

	// output
	if(OUTPUT){
		suffix_array_write(SA, n, c_file, "sa");
	}

	#if DEBUG
	if(MODE==1 || MODE==2)//sais or saca-k	
		suffix_array_print(SA, (unsigned char*)str_int, min(10,n), sizeof(int_t));	
	else
		suffix_array_print(SA, (unsigned char*)str, min(10,n), sizeof(char));
	#endif

	free(SA);
	free(str_int);
	free(str);

return 0;
}
