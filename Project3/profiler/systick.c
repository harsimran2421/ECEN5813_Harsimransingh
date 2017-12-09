#include <MKL25Z4.H>
#include "systick.h"
#include "DMA.h"

static volatile unsigned int DelayTimerTick = 0;
uint8_t overflow;

volatile unsigned int Ticker[4];
void InitSysTick()
{ SysTick->LOAD = 0X00FFFFFF; // Set the Reload to the interrupt at our desired frequency
  SysTick->VAL = 0;
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk   |SysTick_CTRL_ENABLE_Msk;

	//Important!  Since the Systick is part of the Cortex core and NOT a kinetis peripheral
	// its Interrupt line is not passed through NVIC.   You need to make sure that
	//the SysTickIRQ function is populated in the vector table.  See the kinetis_sysinit.c file
}

void SysTick_Handler()
{

	overflow += 1;

}

void Delay_mS(unsigned int TicksIn_mS)
{
	DelayTimerTick = 0;

	while(DelayTimerTick<TicksIn_mS)
	{
	}
}
