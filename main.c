/*
 * Induced Suffix Sorting and LCP array construction for String Collections
 *
 * Authors: Felipe A. Louza, Simon Gog, Guilherme P. Telles
 * contact: louza@ic.unicamp.br
 * 
 * version 1.2
 * 21/06/2016
 *
 */

#include <stdio.h>
#include <errno.h>
#include <time.h>

#include "lib/file.h"
#include "lib/suffix_array.h"
#include "lib/lcp_array.h"
#include "external/malloc_count/malloc_count.h"
#include "src/gsais.h"
#include "src/gsaca-k.h"

#ifndef DEBUG
        #define DEBUG   0
#endif


/*******************************************************************/

int main(int argc, char** argv){

int VALIDATE=0, MODE=0, OUTPUT=0, LCP_COMPUTE=0;
time_t t_start=0, t_total=0;
clock_t c_start=0, c_total=0;

	if(argc!=8){
		dies(__func__,"argc!=4");
	}

	unsigned char **R;
	int_t i, n=0;
	int   k;

	char* c_dir = argv[1];
	char* c_file = argv[2];

	sscanf(argv[3], "%d", &k);
	sscanf(argv[4], "%u", &MODE);
	sscanf(argv[5], "%u", &LCP_COMPUTE);
	sscanf(argv[6], "%u", &VALIDATE);
	sscanf(argv[7], "%u", &OUTPUT);

	if(MODE>6) LCP_COMPUTE=1;

	file_chdir(c_dir);

	//disk access
	R = (unsigned char**) file_load_multiple(c_file, k, &n);
	if(!R){
		fprintf(stderr, "Error: less than %d strings in %s\n", k, c_file);
		return 0;
	}

	unsigned char *str = NULL;
	int_t  *str_int = NULL;
	
	//concatenate strings
	if(MODE==1 || MODE==2){//sais or saca-k (int)	
		str_int = cat_int(R, k, &n);
		
		#if DEBUG
		int_t i;
		for(i=0;i<min(10,n); i++)
			 printf("%" PRIdN ") %" PRIdN "\n", i, str_int[i]);
		printf("\n");
		#endif
	}
	else{ // sais, saca-k, gsais, gsaca-k (char)
		str = cat_char(R, k, &n);
		#if DEBUG
		int_t i;
		for(i=0;i<min(10,n); i++)
			 printf("%" PRIdN ") %d\n", i, str[i]);
		printf("\n");
		#endif
	}

	printf("K = %" PRId32 "\n", k);
	printf("N = %" PRIdN "\n", n+1);
	printf("sizeof(int) = %zu bytes\n", sizeof(int_t));

	#if DEBUG
		printf("R:\n");
		for(i=0; i<min(5,k); i++)
			printf("%" PRIdN ") %s (%zu)\n", i, R[i], strlen((char*)R[i]));
	#endif

	//free memory
	for(i=0; i<k; i++)
		free(R[i]);
	free(R);

	int_t *SA = (int_t*) malloc(n*sizeof(int_t));
	for(i=0; i<n; i++) SA[i]=0;
	int_t depth=0;

	int_t *LCP = NULL;	
	if(LCP_COMPUTE){
		LCP = (int_t*) malloc(n*sizeof(int_t));
		for(i=0; i<n; i++) LCP[i]=0;
	}

	time_start(&t_total, &c_total);
	time_start(&t_start, &c_start);

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
			depth = gSACA_K((unsigned char*)str, (uint_t*)SA, n, 256, sizeof(char), 0, 1);//separator=1
			break;

 		case 7: printf("## gSAIS+LCP ##\n"); 
			depth = gSAIS_LCP((unsigned char*)str, SA, LCP, n, 256, sizeof(char), 0, 1);//separator=1
			break;

 		case 8: printf("## gSACA_K+LCP ##\n"); 
			depth = gSACA_K_LCP((unsigned char*)str, (uint_t*)SA, LCP, n, 256, sizeof(char), 0, 1);//separator=1
			break;
		
		default: break;
	}

	fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));

	if(LCP_COMPUTE && MODE<7){
		time_start(&t_start, &c_start);
		if(MODE==1 || MODE==2)
			lcp_PHI_int((int_t*)str_int, SA, LCP, n, sizeof(int_t));
		else
			lcp_PHI((unsigned char*)str, SA, LCP, n, sizeof(char), 1);//separator=1
		printf("PHI-algorithm:\n");
		fprintf(stderr,"%.6lf\n", time_stop(t_start, c_start));
	}

        printf("total:\n");
        fprintf(stderr,"%.6lf\n", time_stop(t_total, c_total));

	#if DEBUG
	if(MODE==1 || MODE==2)//sais or saca-k	
		if(LCP_COMPUTE)	lcp_array_print((unsigned char*)str_int, SA, LCP, min(20,n), sizeof(int_t));	
		else suffix_array_print((unsigned char*)str_int, SA, min(10,n), sizeof(int_t));	
	else
		if(LCP_COMPUTE)	lcp_array_print((unsigned char*)str, SA, LCP, min(20,n), sizeof(char));	
		else suffix_array_print((unsigned char*)str, SA, min(10,n), sizeof(char));
	#endif


	// validate	
	if(VALIDATE){
		if(MODE==1 || MODE==2){//sais or saca-k	
	        	if(!suffix_array_check((unsigned char*)str_int, SA, n, sizeof(int_t), 0)) printf("isNotSorted!!\n");
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}
		else if(MODE==3 || MODE==4){
	        	if(!suffix_array_check((unsigned char*)str, SA, n, sizeof(char), 0)) printf("isNotSorted!!\n");//compares until the sentinel=0
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}
		else if(MODE==5 || MODE==6 || MODE==7 || MODE==8){
	        	if(!suffix_array_check((unsigned char*)str, SA, n, sizeof(char), 1)) printf("isNotSorted!!\n");//compares until the separator=1
		        else printf("isSorted!!\ndepth = %" PRIdN "\n", depth);
		}

		if(LCP_COMPUTE){
			if(MODE==1 || MODE==2)//sais or saca-k	
	                	if(!lcp_array_check((unsigned char*)str_int, SA, LCP, n, sizeof(int_t), 1)) printf("isNotLCP!!\n");
	        	        else printf("isLCP!!\n");
			else
	                	if(!lcp_array_check((unsigned char*)str, SA, LCP, n, sizeof(char), 1)) printf("isNotLCP!!\n");
	        	        else printf("isLCP!!\n");
		}

	}
	else printf("depth = %" PRIdN "\n", depth);

	// output
	if(OUTPUT){
		if(LCP_COMPUTE) lcp_array_write(SA, LCP, n, c_file, "sa_lcp");
		else suffix_array_write(SA, n, c_file, "sa");
	}

	free(SA);
	if(LCP_COMPUTE){
		free(LCP);
	}
	if(MODE==1 || MODE==2) free(str_int);
	else free(str);

return 0;
}
