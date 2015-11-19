#include "gsais.h"

#define chr(i) (cs==sizeof(int_t)?((int_t*)s)[i]:((unsigned char *)s)[i])

#define false 0 
#define true 1  

#define DEBUG 0
#define DEPTH 0	 // compute time and size of reduced problem for each recursion call
#define PHASES 0 // compute time for each phase

#if m64
	const int_t EMPTY=0xffffffffffffffff; 
#else
	const int EMPTY=0xffffffff; 
#endif

unsigned char mask[]={0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};  

// compute the head or end of each bucket
void getBuckets(int_t *s, int_t *bkt, int_t n, int_t K, int cs, int end) { 
  int_t i, sum=0;
  for(i=0; i<K; i++) bkt[i]=0; // clear all buckets
  for(i=0; i<n; i++) bkt[chr(i)]++; // compute the size of each bucket
  for(i=0; i<K; i++) { sum+=bkt[i]; bkt[i]=end ? sum-1 : sum-bkt[i]; }
}

// compute SAl
void induceSAl(unsigned char *t, int_t *SA, int_t *s, int_t *bkt, 
               int_t n, int_t K, int cs, int level) { 
  int_t i, j;
  getBuckets(s, bkt, n, K, cs, false); // find heads of buckets
//  if(level==0) bkt[0]++; 
  for(i=0; i<n; i++)
    if(SA[i]!=EMPTY) {
	  j=SA[i]-1; 
	  if(j>=0 && !tget(j)) SA[bkt[chr(j)]++]=j;
    }
}

// compute SAs
void induceSAs(unsigned char *t, int_t *SA, int_t *s, int_t *bkt, 
               int_t n, int_t K, int cs, int level) { 
  int_t i, j;
  getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
  for(i=n-1; i>=0; i--)
    if(SA[i]!=EMPTY) {
	  j=SA[i]-1; 
	  if(j>=0 && tget(j)) SA[bkt[chr(j)]--]=j;
    }
}

/*****************************************************************************/
// compute SAl
void induceSAl_generalized(unsigned char *t, int_t *SA, unsigned char *s, int_t *bkt, 
               int_t n, int_t K, int cs, int level, int separator) { 
  int_t i, j;
  getBuckets((int_t*)s, bkt, n, K, cs, false); // find heads of buckets
//  if(level==0) bkt[0]++; 
  for(i=0; i<n; i++)
    if(SA[i]!=EMPTY) {
	  j=SA[i]-1; 
	  if(j>=0 && !tget(j) && chr(j)!=separator) SA[bkt[chr(j)]++]=j;
    }
}

// compute SAs
void induceSAs_generalized(unsigned char *t, int_t *SA, unsigned char *s, int_t *bkt, 
               int_t n, int_t K, int cs, int level, int separator) { 
  int_t i, j;
  getBuckets((int_t*)s, bkt, n, K, cs, true); // find ends of buckets
  for(i=n-1; i>=0; i--)
    if(SA[i]!=EMPTY) {
	  j=SA[i]-1; 
	  if(j>=0 && tget(j) && chr(j)!=separator) SA[bkt[chr(j)]--]=j;
    }
}
/*****************************************************************************/

int_t SAIS(int_t *s, int_t *SA, int_t n, int_t K, int cs, int level) {
  int_t i, j;

  #if PHASES
  time_t t_start_phase = 0.0;
  clock_t c_start_phase = 0.0;
  #endif

  #if DEPTH
  time_t t_start = time(NULL);
  clock_t c_start =  clock();
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  unsigned char *t=(unsigned char *)malloc(n/8+1); // LS-type array in bits

  // stage 1: reduce the problem by at least 1/2

  // Classify the type of each character
  tset(n-2, 0); tset(n-1, 1); // the sentinel must be in s1, important!!!
  for(i=n-3; i>=0; i--) tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);

  int_t *bkt = (int_t *)malloc(sizeof(int_t)*K); // bucket counters

  // sort all the S-substrings
  getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
  for(i=0; i<n; i++) SA[i]=EMPTY;
  for(i=n-2; i>=0; i--)
    if(isLMS(i)) SA[bkt[chr(i)]--]=i;
  SA[0]=n-1; // set the single sentinel LMS-substring

  induceSAl(t, SA, s, bkt, n, K, cs, level); 
  induceSAs(t, SA, s, bkt, n, K, cs, level); 
  free(bkt);

  // compact all the sorted substrings into the first n1 items of s
  // 2*n1 must be not larger than n (proveable)
  int_t n1=0;
  for(i=0; i<n; i++)
    if(isLMS(SA[i]))
      SA[n1++]=SA[i];

  // Init the name array buffer
  for(i=n1; i<n; i++) SA[i]=EMPTY;

  // find the lexicographic names of all substrings
  int_t name=0;
  int_t prev=-1;
  for(i=0; i<n1; i++) {
    int_t pos=SA[i]; int diff=false;
    int_t d;
    for(d=0; d<n; d++)
      if(prev==-1 || pos+d==n-1 || prev+d==n-1 ||
         chr(pos+d)!=chr(prev+d) ||
         tget(pos+d)!=tget(prev+d))
      { diff=true; break; }
      else
        if(d>0 && (isLMS(pos+d) || isLMS(prev+d)))
          break;

    if(diff) 
      { name++; prev=pos; }
	  pos=(pos%2==0)?pos/2:(pos-1)/2;
    SA[n1+pos]=name-1; 
  }
  for(i=n-1, j=n-1; i>=n1; i--)
	  if(SA[i]!=EMPTY) SA[j--]=SA[i];

  #if PHASES
  if(!level){
	printf("phase 1:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif
 
  // s1 is done now
  int_t *SA1=SA, *s1=SA+n-n1;

  // stage 2: solve the reduced problem
  int_t depth=1;
  // recurse if names are not yet unique
  if(name<n1) {
    depth += SAIS((int_t*)s1, SA1, n1, name, sizeof(int_t), level+1);
  } else{ // generate the suffix array of s1 directly
    for(i=0; i<n1; i++) SA1[s1[i]] = i;
  }

  // stage 3: induce the result for the original problem
  bkt = (int_t *)malloc(sizeof(int_t)*K); // bucket counters

  // put all left-most S characters into their buckets
  getBuckets(s, bkt, n, K, cs, true); // find ends of buckets
  j=0;
  for(i=1; i<n; i++)
    if(isLMS(i)) s1[j++]=i; // get p1

  for(i=0; i<n1; i++) SA1[i]=s1[SA1[i]]; // get index in s1
  for(i=n1; i<n; i++) SA[i]=EMPTY; // init SA[n1..n-1]
  for(i=n1-1; i>=0; i--) {
    j=SA[i]; SA[i]=EMPTY;
    if(level==0 && i==0)
      SA[0]=n-1;
    else
      SA[bkt[chr(j)]--]=j;
  }
  
  #if PHASES
  if(!level){
	printf("phase 2:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  induceSAl(t, SA, s, bkt, n, K, cs, level); 

  #if PHASES
  if(!level){
	printf("phase 3:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  induceSAs(t, SA, s, bkt, n, K, cs, level); 

  free(bkt); 
  free(t);

  #if PHASES
  if(!level){
	printf("phase 4:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if DEPTH
  printf("depth %" PRIdN ":\n", depth);
  time_stop(t_start, c_start);
  #endif

return depth;
}

int_t gSAIS(unsigned char *s, int_t *SA, int_t n, int_t K, int cs, int level, unsigned char separator) {
  int_t i, j;
  
  #if PHASES
  time_t t_start_phase = 0.0;
  clock_t c_start_phase = 0.0;
  #endif

  #if DEPTH
  time_t t_start = time(NULL);
  clock_t c_start =  clock();
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  unsigned char *t=(unsigned char *)malloc(n/8+1); // LS-type array in bits

  // stage 1: reduce the problem by at least 1/2

  // Classify the type of each character
  tset(n-2, 0); tset(n-1, 1); // the sentinel must be in s1, important!!!
  for(i=n-3; i>=0; i--) tset(i, (chr(i)<chr(i+1) || (chr(i)==chr(i+1) && tget(i+1)==1))?1:0);

  int_t *bkt = (int_t *)malloc(sizeof(int_t)*K); // bucket counters

  // sort all the S-substrings
  getBuckets((int_t*)s, bkt, n, K, cs, true); // find ends of buckets
  for(i=0; i<n; i++) SA[i]=EMPTY;

  // FELIPE
  int_t tmp=bkt[separator]--;// shift one position left of bkt[separator]

  SA[0]=n-1; // set the single sentinel LMS-substring

  SA[tmp]=SA[0]-1;// insert the last separator at the end of bkt[separator]

  int_t p=n-2;

  for(i=n-2; i>=0; i--){
    if(isLMS(i)){

      if(chr(i)==separator) // FELIPE
        SA[bkt[chr(p)]++]=EMPTY; // removes LMS-positions that induces separator suffixes

      SA[bkt[chr(i)]--]=i;
      p=i;
    }
  }

  induceSAl_generalized(t, SA, s, bkt, n, K, cs, level, separator); 
  induceSAs_generalized(t, SA, s, bkt, n, K, cs, level, separator); 

  // insert separator suffixes in their buckets
  bkt[separator]=1; // FELIPE
  for(i=0; i<n-1; i++) 
    if(chr(i)==separator)
      SA[bkt[chr(i)]++]=i;
  
  free(bkt);

  // compact all the sorted substrings into the first n1 items of s
  // 2*n1 must be not larger than n (proveable)
  int_t n1=0;
  for(i=0; i<n; i++)
    if(isLMS(SA[i]))
      SA[n1++]=SA[i];


  // Init the name array buffer
  for(i=n1; i<n; i++) SA[i]=EMPTY;

  // find the lexicographic names of all substrings
  int_t name=0, prev=-1;
  for(i=0; i<n1; i++) {

    int_t pos=SA[i]; int diff=false;
    int_t d;
    for(d=0; d<n; d++)
      if(prev==-1 || pos+d==n-1 || prev+d==n-1 ||
         chr(pos+d)!=chr(prev+d) ||
         (chr(pos+d)==separator && chr(prev+d)==separator) || // $_i < $_j iff i < j
         tget(pos+d)!=tget(prev+d) // FELIPE
      )
      { 
	diff=true; break;
      }
      else
        if(d>0 && (isLMS(pos+d) || isLMS(prev+d)))
          break;

    if(diff){
      name++; 
      prev=pos; 
    }

    pos=(pos%2==0)?pos/2:(pos-1)/2;
    SA[n1+pos]=name-1; 
  }

  for(i=n-1, j=n-1; i>=n1; i--)
	  if(SA[i]!=EMPTY) SA[j--]=SA[i];
  
  #if PHASES
  if(!level){
	printf("phase 1:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  // s1 is done now
  int_t *SA1=SA, *s1=SA+n-n1;

  // stage 2: solve the reduced problem

  int_t depth=1;
  // recurse if names are not yet unique
  if(name<n1) {
    depth += SAIS((int_t*)s1, SA1, n1, name, sizeof(int_t), level+1);
  } else{ // generate the suffix array of s1 directly
    for(i=0; i<n1; i++) SA1[s1[i]] = i;
  }
  
  #if PHASES
  if(!level){
	printf("phase 2:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  // stage 3: induce the result for the original problem

  bkt = (int_t *)malloc(sizeof(int_t)*K); // bucket counters

  // put all left-most S characters into their buckets
  getBuckets((int_t*)s, bkt, n, K, cs, true); // find ends of buckets
  j=0;
  for(i=1; i<n; i++)
    if(isLMS(i)) s1[j++]=i; // get p1

  for(i=0; i<n1; i++) SA1[i]=s1[SA1[i]]; // get index in s1
  for(i=n1; i<n; i++) SA[i]=EMPTY; // init SA[n1..n-1]

  tmp=bkt[separator]--;// shift one position left of bkt[separator]
  for(i=n1-1; i>=0; i--) {
      j=SA[i]; SA[i]=EMPTY;
      if(level==0 && i==0)
          SA[0]=n-1;
      else
          SA[bkt[chr(j)]--]=j;
  }
  
  SA[tmp]=SA[0]-1;// insert the last separator at the end of bkt[separator]
  induceSAl_generalized(t, SA, s, bkt, n, K, cs, level, separator); 
  
  #if PHASES
  if(!level){
	printf("phase 3:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif

  #if PHASES
  if(!level){
	t_start_phase = time(NULL);
	c_start_phase =  clock();
  }
  #endif

  induceSAs_generalized(t, SA, s, bkt, n, K, cs, level, separator); 
  
  free(bkt); 
  free(t);

  #if DEPTH
  printf("depth %" PRIdN ":\n", depth);
  time_stop(t_start, c_start);
  #endif
  
  #if PHASES
  if(!level){
	printf("phase 4:\n");
	time_stop(t_start_phase, c_start_phase);
  }
  #endif


return depth;
}

