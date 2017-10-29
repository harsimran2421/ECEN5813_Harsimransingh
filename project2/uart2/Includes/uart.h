/*
 * uart.h
 *
 *  Created on: Oct 26, 2017
 *      Author: modak
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_




#include <stdio.h>
#include <stdint.h>
#include "MKL25Z4.h"
#include "circbuf.h"
/*#if baud==115200
	#define uart_reg->UART0_BDL 0x17
	#define uart_reg->UART0_BDH 0x00
	#define uart_reg->UART0_C4 0x0F
#elif baud==38400
	#define uart_reg->UART0_BDL 0x44
	#define uart_reg->UART0_BDH 0x00
	#define uart_reg->UART0_C4 0x0F
#else baud==57200
	#define uart_reg->UART0_BDL 0x2E
	#define uart_reg->UART0_BDH 0x00
	#define uart_reg->UART0_C4 0x0F
#endif*/



CB_t *create_buffer(CB_t *cbuf);

int UART_configure(void);

int UART_send(char data);

int UART_send_n(uint8_t *data, int length);

int UART_receive(void);

int UART_receive_n(uint8_t *data,int length);

void UART0_IRQHandler();


#endif /* INCLUDES_UART_H_ */

