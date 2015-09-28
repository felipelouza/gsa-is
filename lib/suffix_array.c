#include "suffix_array.h"


#define chr(i) (cs==sizeof(int_t)?((int_t*)T)[i]:((unsigned char *)T)[i])

/*******************************************************************/

int_t suffix_array_print(int_t *SA, unsigned char *T, size_t len, int cs){

int_t i;
	for(i=0; i<len; i++){

		printf("%" PRIdN ") %" PRIdN "\t", i, SA[i]);
	
		int_t j=SA[i];
		for(j=SA[i]; (j<SA[i]+5); j++)
			printf("%" PRIdN " ", chr(j));
		printf("\n");
	}

return 1;
}

/*******************************************************************/

int_t sleq(unsigned char *T, int_t a, int_t b, size_t len, int cs, unsigned char sentinel) {

	size_t i;

	for(i=0; i<len; i++){

	        if (chr(a) < chr(b))
			return 1;
	        else if (chr(a) > chr(b))
        	        return 0;
		else if(chr(a)==sentinel && chr(b)==sentinel){// $_i < $_j iff i < j
			if(a < b) 
				return 1;
			else 	
				return 0;
		}
		a++;
		b++;
        }

return 1;
} 

/*******************************************************************/

int_t suffix_array_check(int_t *SA, unsigned char *T, size_t len, int cs, unsigned char sentinel){

	int_t i,j,k;
	
	for (i = 0; i < len-1;  i++) {
		size_t min = SA[i+1]<SA[i]?(len-SA[i]):(len-SA[i+1]);
		if (!sleq(T, SA[i], SA[i+1], min, cs, sentinel)){

			printf("#%" PRIdN ") %" PRIdN ", %" PRIdN "&\n", i, SA[i], SA[i+1]);

			for(j=SA[i], k=SA[i+1]; (j<SA[i]+5); j++, k++)
				printf("%" PRIdN " | %" PRIdN "\n", chr(j), chr(k));
			printf("\n");

			return 0;
		}
	}

	unsigned char *tmp = (unsigned char*) malloc(len*sizeof(unsigned char));

	for (i = 0; i < len;  i++) 
		tmp[i] = 0;

	for (i = 0; i < len;  i++) 
		tmp[SA[i]] = 1;
	
	for (i = 0; i < len;  i++){ 
		if(!tmp[i]){
			free(tmp);
			fprintf(stderr, "Error: not a permutation\n");
			return 0;
		}
	}

	free(tmp);
	
return 1;  
}

/*******************************************************************/
