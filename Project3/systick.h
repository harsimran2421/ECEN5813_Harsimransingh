/*
 * systick.h
 *
 *  Created on: Nov 30, 2017
 *      Author: modak
 */

#ifndef INCLUDES_SYSTICK_H_
#define INCLUDES_SYSTICK_H_

void InitSysTick();
void SysTick_Handler();
void Delay_mS(unsigned int TicksIn_mS);

#endif /* INCLUDES_SYSTICK_H_ */
