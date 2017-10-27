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

#if baud==115200
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
#endif

int UART_configure(void);

int UART_send(char *data_send);

int UART_send_n(char *data_send_n, int length);

int UART_receive(char *data_receive);

int UART_receive_n(char *data_receive_n,int length);

int UART0_IRQHandler(void);


#endif /* INCLUDES_UART_H_ */
