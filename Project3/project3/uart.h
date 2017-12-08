/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/29/2017
 * *
 * *   File: uart.h
 * *
 * *   Description: Header file for uart communication 
 * *     -UART_congfig
 * *     -UART_send
 * *     -UART_send_n
 * *     -UART_recieve
 * *     -UART_receive_n
 * *	 -UART0_IRQHandler
 * *
 * *
 * ********************************************************
 header  file for function called "uart"
 ******************************************/

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
/**
 * Create buffer with CB_t the struct defined in cirbuf.h
 *
 * This is used to create transmit and receive buffer.
 * 
 *
 */

CB_status add_to_buffer(uint8_t *str_ptr);
/**
 * Add items to the buffer. 
 *
 * This is used to add items to the buffer when transmitting and receiving. It uses CB_status enum to 
 * give status about the buffer.
 */

void UART_configure(void);
/**
 * Function to configure UART
 *
 * This function uses register masks to configure UART0 for receiving, transmitting and handling interrupts.
 * It enables MCGFLL clock, disables the uart initially, sets up the baud rate, enables Transmit and Receive 
 * interrupts..
 */

void UART_send(uint8_t *data);
/**
 * Function to transmit
 *
 * This function takes a pointer to the data. It puts the data in UART0_D register to transmit.
 * 
 *
 */

void UART_send_n(uint8_t *data, uint8_t length);
/**
 * Function to transmit data of length n
 *
 * This function takes pointer to the data and length of the data. It puts the data in UART0_D register one by one 
 * to transmit.
 *
 */

void UART_receive(uint8_t *data);
/**
 * Function to receive data 
 *
 * This function takes pointer to the data. It puts the data from UART0_D register to pointed address.
 * 
 *
 */

void UART_receive_n(uint8_t *data,uint8_t length);
/**
 * Function to receive data of length n
 *
 * This function takes pointer to the data and the length of the data. 
 * It puts the data from UART0_D register to pointed address one by one.
 * 
 *
 */

void UART0_IRQHandler();
/**
 * Function to handle interrupt. 
 *
 * This function is invoked when the transmit and receive interrupt are enabled. 
 * It loads the data from the buffer into a variable and then transmits the data using send function, removes
 * the item. When the buffer count reaches 0, it disables the Transmit interrupt.
 * The recieved data is being stored in the buffer once the receive interrupt is on.
 * 
 *
 */


#endif /* INCLUDES_UART_H_ */

