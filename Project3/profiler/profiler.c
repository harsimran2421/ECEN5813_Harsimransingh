#include <stdio.h>
#include <stdint.h>
#include "DMA.h"
#include "profiler.h"
#include "MKL25Z4.h"
#include "binary_logger.h"
#include <stdlib.h>

void profiler_run()
{

	uint8_t src[]="harsimrans";//calloc(10,sizeof(uint8_t));
	uint8_t dst[10]="aaaaaaaaaa";//malloc(10*sizeof(uint8_t));
	Initailize_dma();
	InitSysTick();
	memmove_dma(src, dst,10);
	uint32_t end = SysTick -> VAL;
	uint32_t elapsed_count=((SysTick->LOAD)-end);
	float systick_value=(float)elapsed_count*(float)((1)/(float)(DEFAULT_SYSTEM_CLOCK));
	uint8_t a=0;
	FRDM_log_data(dst,10);
	//my_itoa((uint32_t)systick_value, (int8_t *)&systick_value,10);
	//FRDM_log_data((uint8_t*)&(systick_value),1);

}

//void initialize_counter()
//{
//
//	SIM->SCGC6 |= 0x01000000;
//	SIM->SOPT2 |= 0x01000000;
//	TPM0->SC = 0x0;
//	TPM0->MOD = 0xFFFF;
//	TPM0->CNT = 0x0;
//	TPM0->SC = 0X00000080;
//}
//
//void counter_start()
//{
//	TPM0->CNT = 0x0;
//	TPM0->SC = 0x00000008;
//}
//
//void counter_stop()
//{
//	TPM0->SC = 0x0;
//}
