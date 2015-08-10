#include "hw3.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define chunk_size(c) ((*((size_t*)c))& ~(size_t)3 )

void * my_malloc(int bytes){
  void * retval = malloc(bytes);
  if (retval > 0){
    fprintf(stderr,"malloc'd chunk at 0x%p, size requested %d, size received %d\n",
        retval,bytes,chunk_size(retval-1));
  }
  return retval;
}

void my_free(void * ptr){
  fprintf(stderr,"free'd chunk at 0x%p, size %d\n",ptr,chunk_size(ptr-1));
  free(ptr);
}

#define MAX_ALLOCATIONS 10
void * allocs[MAX_ALLOCATIONS];

int main(int argc, char** argv) {

  init_gc();

  for(int i=0;i<MAX_ALLOCATIONS;i++) 
    allocs[i]=my_malloc(i*2+128); 		 

  for(int i=0;i<MAX_ALLOCATIONS;i++) 
    my_free(allocs[i]);
  gc();
}
