#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
void main()
{

  struct timeval start,end;
  uint8_t *src=malloc(500*sizeof(uint8_t));
  uint8_t *dst=malloc(500*sizeof(uint8_t));
	uint8_t arr[10]="harsimrans";
	//src=arr;

  gettimeofday(&start,NULL);
  
  my_memmove(src,dst,500);
  
  gettimeofday(&end,NULL);
  printf("\n%ld\n",start.tv_usec);
  printf("\n%ld\n",end.tv_usec);
  //for(uint8_t i=0; i<10;i++)
  //{
   // printf("\n%c\n",*(dst+i));
  //}
}


