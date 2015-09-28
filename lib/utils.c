#include "utils.h"

/**********************************************************************/


double time_stop(time_t t_time, clock_t c_clock){

	double aux1 = (clock() - c_clock) / (double)(CLOCKS_PER_SEC);
	double aux2 = difftime (time(NULL),t_time);
	
	printf("CLOCK = %lf TIME = %lf\n", aux1, aux2);
	
	return aux2;
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
/**********************************************************************/
