/*
 * Felipe A. Louza (louza@ic.unicamp.br)
 * 01/09/2015
 *
 */

#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "lib/file.h"
#include "lib/utils.h"
#include "lib/suffix_array.h"
#include "external/malloc_count/malloc_count.h"
#include "gsais.h"
#include "gsaca-k.h"

#define DEBUG 0

/*******************************************************************/
unsigned int* cat_int(unsigned char** R, int k, int *n){

	(*n)++; //add 0 at the end

	int i, j, l=0;
	unsigned int *str_int = (unsigned int*) malloc((*n)*sizeof(unsigned int));

	for(i=0; i<k; i++){
		for(j=0; j<strlen((char*)R[i]); j++)
			str_int[l++] = R[i][j]+(k+1);
		str_int[l++] = i+1; //add $_i as separator
	}
	
	str_int[l]=0;

return str_int;
}
/*******************************************************************/
unsigned char* cat_char(unsigned char** R, int k, int *n){

	(*n)++; //add 0 at the end

	int i, j, l=0;
	unsigned char *str = (unsigned char*) malloc((*n)*sizeof(unsigned char));

	for(i=0; i<k; i++){
		for(j=0; j<strlen((char*)R[i]); j++)
			str[l++] = R[i][j]+1;
		str[l++] = 1; //add 1 as separator
	}

	str[l]=0;

return str;
}

/*******************************************************************/

int main(int argc, char** argv){

int VALIDATE=0, MODE=0;

	if(argc!=6){
		dies(__func__,"argc!=4");
	}

	unsigned char **R;
	int k, i, n=0;

	char* dir = argv[1];
	char* file = argv[2];

	sscanf(argv[3], "%d", &k);
	sscanf(argv[4], "%u", &MODE);
	sscanf(argv[5], "%u", &VALIDATE);

	file_chdir(dir);

	//disk access
	R = (unsigned char**) file_load_multiple(file, k, &n);
	if(!R){
		fprintf(stderr, "Error: less than %d strings in %s\n", k, file);	
		return 0;
	}

	printf("K = %d\n", k);
	printf("N = %d\n", n+1);

	unsigned char *str = NULL;
	unsigned int  *str_int = NULL;
	
	//concatenate strings
	if(MODE==1 || MODE==2){//sais or saca-k	
		str_int = cat_int(R, k, &n);
		
		#if DEBUG
		int i=0;
		for(;i<n; i++)
			 printf("%d) %d\n", i, str_int[i]);
		printf("\n");
		#endif
	}
	else if(MODE==3 || MODE==4){
		
		str = cat_char(R, k, &n);
		#if DEBUG
		int i=0;
		for(;i<n; i++)
			 printf("%d) %d\n", i, str[i]);
		printf("\n");
		#endif
	}

	//free memory
	for(i=0; i<k; i++)
		free(R[i]);
	free(R);


	//sorted array
	int *SA = (int*) malloc(n*sizeof(int));
	int depth=0;
	//sais, saca-k, gsais, gsaca-k

	time_t t_start = time(NULL);
	clock_t c_start =  clock();

	switch(MODE){
		case 1: printf("## SAIS ##\n");
			depth = SAIS((unsigned char*)str_int, SA, n, 256+k, sizeof(int), 0);
			break;

		case 2: printf("## SACA_K ##\n"); 
			depth = SACA_K((unsigned char*)str_int, (unsigned int*)SA, n, 256+k, n, sizeof(int), 0);
			break;

		case 3: printf("## gSAIS ##\n"); 
			depth = gSAIS((unsigned char*)str, SA, n, 256, sizeof(char), 0, 1);//separator=1
			break;

		case 4: printf("## gSACA_K ##\n"); 
			depth = gSACA_K((unsigned char*)str, (unsigned int*)SA, n, 256, n, sizeof(char), 0, 1);
			break;

		default: break;
	}

	time_stop(t_start, c_start);

	// validate	
	if(VALIDATE){
		if(MODE==1 || MODE==2){//sais or saca-k	
	        	if(!suffix_array_check(SA, (unsigned char*)str_int, n, sizeof(int), 0)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %d\n", depth);
		}
		else if(MODE==3 || MODE==4){
	        	if(!suffix_array_check(SA, (unsigned char*)str, n, sizeof(char), 1)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %d\n", depth);
		}
	}
	else printf("depth = %d\n", depth);

	#if DEBUG
	if(MODE==1 || MODE==2)//sais or saca-k	
		suffix_array_print(SA, (unsigned char*)str_int, min(10,n), sizeof(int));	
	else if(MODE==3 || MODE==4)
		suffix_array_print(SA, (unsigned char*)str, min(10,n), sizeof(char));
	#endif

	#if DEBUG
		printf("R:\n");
		for(i=0; i<k; i++)
			printf("%d) %s (%zu)\n", i, R[i], strlen((char*)R[i]));
	#endif


	free(SA);
	free(str_int);
	free(str);

return 0;
}
