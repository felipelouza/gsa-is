#include "utils.hpp"

#define chr(i) (cs==sizeof(int_t)?((int_t*)T)[i]:((unsigned char *)T)[i])

/**********************************************************************/

void time_start(time_t *t_time, clock_t *c_clock){

	*t_time = time(NULL);
	*c_clock =  clock();
}

double time_stop(time_t t_time, clock_t c_clock){

	double aux1 = (clock() - c_clock) / (double)(CLOCKS_PER_SEC);
	double aux2 = difftime (time(NULL),t_time);
	
	printf("CLOCK = %lf TIME = %lf\n", aux1, aux2);
	
	return aux1;
}


/**********************************************************************/
void die(const char* where) {

	printf("Error at %s: %s.\n",where,errno ? strerror(errno) : "errno not set");
	exit(errno?errno:1);
}
 
void dies(const char* where, char* format, ...) {

	int_t err = errno;
	va_list val;

	printf("Error at %s: %s.\n",where,errno ? strerror(errno) : "errno not set");
	va_start(val,format);
	vprintf(format,val);
	va_end(val);
	printf("\n");

	exit(err ? err : 1);
}
/**********************************************************************/
int_t print_char(char* A, int_t n){

	int_t i;
	for(i=0; i<n; i++)	
		printf("%" PRIdN ") %c\n", i, A[i]);

	printf("\n");

return 0;
}
/**********************************************************************/
int_t print_int(int_t* A, int_t n){

	int_t i;
	for(i=0; i<n; i++)	
		printf("%" PRIdN ") %" PRIdN "\n", i, A[i]);

	printf("\n");

return 0;
}
/**********************************************************************/
int_t min_range(int_t* A, int_t l, int_t r){


	if(r>l)return 0;

	printf("[l, r] = [%" PRIdN ", %" PRIdN "]\n", l, r);

	int_t min = INT_MAX;
	int_t i;
	for(i=l; i<=l; i++)
		min = (A[i]<min?A[i]:min);

	printf("min = %" PRIdN "\n", min);

return min;
}
/*******************************************************************/
int_t* cat_int(unsigned char** R, int k, int_t *n){

	(*n)++; //add 0 at the end

	int_t i, j;
	int_t l=0;
	int_t *str_int = (int_t*) malloc((*n)*sizeof(int_t));

	for(i=0; i<k; i++){
		int_t m = strlen((char*)R[i]);
		for(j=0; j<m; j++){
			//removes symbols > 255
			if(R[i][j]+1<256) str_int[l++] = R[i][j]+(k+1);
			else (*n)--;
		}
//		for(j=0; j<m; j++)
//			str_int[l++] = R[i][j]+(k+1);
		str_int[l++] = i+1; //add $_i as separator
	}
	
	str_int[l++]=0;
        if(*n>l){
		str_int = (int_t*) realloc(str_int, (l)*sizeof(int_t));
		printf("N = %" PRIdN "\n", l);
	}
	*n = l;

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
		//removes empty strings
		if(m==0){
			(*n)--;
			continue;
		}
		for(j=0; j<m; j++){
			//removes symbols > 255
			if(R[i][j]+1<256 && R[i][j]+1>0) str[l++] = R[i][j]+1;
			else (*n)--;
		}
		str[l++] = 1; //add 1 as separator
	}

	str[l++]=0;
        if(*n>l){
		str = (unsigned char*) realloc(str, (l)*sizeof(unsigned char));
		printf("N = %" PRIdN "\n", l);
	}
	*n = l;

return str;
}

/**********************************************************************/
double log2(double i){
	return log(i)/log(2);
}
/**********************************************************************/

int document_array_check(unsigned char *T, int_t *SA, int_t *DA, uint_t n, int cs, unsigned char separator, int_t k){

	uint_t i, count=k;
	int_t* R = (int_t*) malloc(n*sizeof(int_t));

	for(i=n-1; i>0;i--){
		if(chr(i)==separator) count--;
		R[i]=count;
	}
	R[0]=0;

	for(i=0; i<n;i++){
		if(DA[i]!=R[SA[i]]){
			free(R);
			return 0;
		}
	}

	free(R);	
	
return 1;
}

/*******************************************************************/

int document_array_print(unsigned char *T, int_t *SA, int_t *DA, size_t n, int cs){

	uint_t i;
        for(i=0; i<n; i++){

                printf("%" PRIdN ") %" PRIdN "\t %" PRIdN "  \t", i, SA[i], DA[i]);

                int_t j=SA[i];
                for(j=SA[i]; (j<SA[i]+10); j++)
                        printf("%" PRIdN " ", chr(j));
                printf("\n");
        }

return 1;
}

/*******************************************************************/ 

int document_array_write(int_t *DA, int_t n, char* c_file, const char* ext){

        FILE *f_out;
        char *c_out = (char*) malloc((strlen(c_file)+strlen(ext))*sizeof(char));
        
        sprintf(c_out, "%s.%s", c_file, ext);
        f_out = fopen(c_out, "wb");
        
	int_t i;
	for(i=0; i<n; i++){//writes DA 
	        fwrite(&DA[i], sizeof(int_t), 1, f_out);
	}

        fclose(f_out);
        free(c_out);

return 1;
}


/*******************************************************************/

int_t document_array_read(int_t** DA, char* c_file, const char* ext){

        FILE *f_in;
        char *c_in = (char*) malloc((strlen(c_file)+strlen(ext))*sizeof(char));

        sprintf(c_in, "%s.%s", c_file, ext);
        f_in = fopen(c_in, "rb");

	fseek(f_in, 0L, SEEK_END);
	size_t size = ftell(f_in);
	rewind(f_in);
	
	int_t n = size/sizeof(int_t);

        *DA = (int_t*) malloc(n*sizeof(int_t));
        fread(*DA, sizeof(int_t), n, f_in);

        fclose(f_in);
        free(c_in);

return n;
}

/*******************************************************************/
