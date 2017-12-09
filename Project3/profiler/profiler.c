#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "profiler.h"
#include <string.h>

#ifdef FRDM
#include "binary_logger.h"
#include "MKL25Z4.h"
#include "DMA.h"
#endif

void profiler_run()
{
#ifdef FRDM
  uint8_t src[]="harsimrans";//calloc(10,sizeof(uint8_t));
  uint8_t dst[10]="aaaaaaaaaa";//malloc(10*sizeof(uint8_t));
  Initailize_dma();
  InitSysTick();
  memmove_dma(src, dst,10);
  uint32_t end = SysTick -> VAL;
  uint32_t elapsed_count=((SysTick->LOAD)-end);
  float systick_value=(float)elapsed_count*(float)((1)/(float)(DEFAULT_SYSTEM_CLOCK));
  FRDM_log_integer(elapsed_time,3);
  //my_itoa((uint32_t)systick_value, (int8_t *)&systick_value,10);
  //FRDM_log_data((uint8_t*)&(systick_value),1);
#endif
#ifdef BBB
  uint8_t *src=calloc(5000,sizeof(uint8_t));
  uint8_t *dst=malloc(5000*sizeof(uint8_t));
  double start_us=gettimeofday(&start,NULL);
  memset(dst,0,10);
  double end_us=gettimeofday(&end,NULL);
  printf("\n%ld\n",start.tv_usec);
  printf("\n%ld\n",end.tv_usec);
  uint32_t elapsed_time=end_us-start_us;
  printf("\n%d\n",elapsed_time);
#endif
}
