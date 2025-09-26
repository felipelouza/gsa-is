#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char M[]={0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
#define tget(i) ( (SAP[(i)/8]&M[(i)%8]) ? 1 : 0 )

#include "gsacak.h"
#include "experiments/external/malloc_count/malloc_count.h" //memory counter

#ifndef DEBUG
#define DEBUG 0
#endif

int main(int argc, char *argv[]){

#if DEBUG
  printf("sizeof(int_t) = %zu bytes\n", sizeof(int_t));
#endif

  unsigned char *Text;
  uint_t n=0;

  // intput data
  if(argc>=2){
    //concatenate all strings s_1, s_2, .., s_d in s_1$s_2$..%s_d$#
    int i = 2, sum=0;
    for(; i<= argc; i++){
      sum += strlen((argv[i-1]))+1;
    }
    n = sum+1;
    Text = malloc(n*sizeof(unsigned char));
    sum=0;
    for(i=2; i<= argc; i++){
      sscanf(argv[i-1], "%s", &Text[sum]);
      sum += strlen((argv[i-1]))+1;
      Text[sum-1]=1;//separator
    }
    Text[n-1]=0;
    printf("N = %d\n", n);
  }
  else{
    fprintf(stderr, "Please, insert at least one string.\n");
    exit(-1);
  }	

  int i, j;
  printf("T^{cat} = ");
  for(i=0;i<n-1;i++){
    if(Text[i]==1) printf("$");
    else printf("%c", Text[i]);
  }
  printf("#\n");

  // allocate
  uint_t *SA = (uint_t *)malloc(n * sizeof(uint_t));
  unsigned char *SAP = (unsigned char *)malloc(n/8+1);

  // sort
  gsacak_sap((unsigned char *)Text, (uint_t*)SA, SAP, n);

  // checking
  uint_t *SA2 = (uint_t *)malloc(n * sizeof(uint_t));
	int_t *LCP = (int_t *)malloc(n * sizeof(int_t));
	gsacak((unsigned char *)Text, (uint_t*)SA2, LCP, NULL, n);

  int check=1;

  // output
  printf("i\tSA\tSAP\tBWT\tLCP\tsuffixes\n");
  for(i = 0; i < n; ++i) {
    char j = (SA[i])? Text[SA[i]-1]:'#';
    if(j==1) j = '$';
    printf("%d\t%d\t%d\t%c\t%d\t",i, SA[i], tget(i), j, LCP[i]);
    for(j = SA[i]; j < n; ++j) {
      if(Text[j]==1) printf("$");
      else printf("%c", Text[j]);
    }
    if(i>1 && (Text[SA[i]+LCP[i]]==1 && tget(i)!=1) ){
      printf("#\t***\n");
      check=0;
    }
    else
      printf("#\n");
  }

  if(!check) printf("## ERROR ##\n");


  // deallocate
  free(SA);
  free(SA2);
  free(LCP);
  free(SAP);
  free(Text);

  return 0;
}

