#ifndef INCLUDES_SYSTICK_H_
#define INCLUDES_SYSTICK_H_
#include <MKL25Z4.H>
#include "systick.h"
#include "DMA.h"

extern uint8_t overflow;

void InitSysTick();

void SysTick_Handler();

void Delay_mS(unsigned int TicksIn_mS);

#endif /* INCLUDES_SYSTICK_H_ */
