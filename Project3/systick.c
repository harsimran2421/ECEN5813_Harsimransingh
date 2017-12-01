/*
 * TPM1_IRQ.c
 *
 *  Created on: Nov 27, 2017
 *      Author: modak
 */
//develop a systick.c
//in the main.c call the init function.
//and use the following code
//int nStart = SYST_CVR;
//Do something
//int nStop = SYST_CVR;

#include <MKL25Z4.H>
#include "systick.h"

static volatile unsigned int DelayTimerTick = 0;

volatile unsigned int Ticker[4];
void InitSysTick()
{ SysTick->LOAD = 41940000/16-1; // Set the Reload to the interrupt at our desired frequency
  SysTick->CTRL = 3;

	//Important!  Since the Systick is part of the Cortex core and NOT a kinetis peripheral
	// its Interrupt line is not passed through NVIC.   You need to make sure that
	//the SysTickIRQ function is populated in the vector table.  See the kinetis_sysinit.c file
}

void SysTick_Handler()
{
	unsigned int i;

	if(DelayTimerTick<0xFFFFFFFF)
	{
		DelayTimerTick++;
	}

	for(i=0;i<4;i++)
	{
		if(Ticker[i]<0xFFFFFFFF)
			{
				Ticker[i]++;
			}
	}
}

void Delay_mS(unsigned int TicksIn_mS)
{
	DelayTimerTick = 0;

	while(DelayTimerTick<TicksIn_mS)
	{
	}
}


