/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/29/2017
 * *
 * *   File: uart.c
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
 * ********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include <MKL25Z4.H>
#include "circbuf.h"

#define MCGFLLCLK 0x04000000
#define OSR_16 0x0F
#define BDH_BAUD_VALUE 0x00
#define BDL_BAUD_57600 0x17
#define buffsize 100

CB_t *transbuf;
CB_t *recbuf;

uint8_t recflag = 0;

CB_t *create_buffer(CB_t *cbuf)
{
	cbuf = malloc(sizeof(CB_t));
	CB_init(&cbuf,100);
	return cbuf;
}

int UART_configure(void)
{
	/*Provide clock to UART0*/
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	/*Selecting MCGFLL clock for UART0*/
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC_MASK & MCGFLLCLK;

	/*Turn Off UART0 to make changes and then enable it */
	UART0_C2 = 0x00;

	/*Adjusting values of BDH and BDL to set baud rate as 57600 */
	UART0_BDH = BDH_BAUD_VALUE;
	UART0_BDL = BDL_BAUD_57600;

	UART0_C4 = UART0_C4_OSR_MASK & OSR_16;

	UART0_C1 = 0x00;

	UART0_C2 = UART0_C2_RE_MASK | UART0_C2_TE_MASK | UART0_C2_RIE_MASK;

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTA_PCR2 = 0x0200;
	PORTA_PCR1 = 0x0200;

	NVIC->ISER[0] |= 0x00001000; /* enable INT12 (bit 12 of ISER[0]) */
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, 2);

}

CB_status add_to_buffer(uint8_t *str_ptr)
{
	while(*(str_ptr) != '\0')				//checks for the null character
	{
		CB_buffer_add_item(transbuf,*str_ptr);		//adds the data to the transmit buffer
		str_ptr++;							// increments the pointer
	}
return No_error;							
}

int UART_send(uint8_t *data)
{
	while(!(UART0->S1 & 0xC0))				
	{
	} 										/* to wait until the transmitting buffer is empty */
	UART0_D = *data;						//write data in the UART0_D register to transmit	
}

int UART_send_n(uint8_t *data, uint8_t length)
{
	for (int i=0;i<=length-1;i++)			//Loop to execute transmitting of data based on the length.
	{
			while(!(UART0->S1 & 0xC0))	
			{
			} 								/* wait for transmit buffer empty */
		UART0_D = *data;					//write data in the UART0_D registerr to transmit
		data++;
	}
}

int UART_receive(uint8_t *data)
{	uint8_t data=0;
	while(!(UART0->S1 & 0x20))
	{
	} /* wait for receive buffer full */
	 *data = UART0_D ; 						// read the char received 	
	 return data;
}

int UART_receive_n(uint8_t *data,int length)	//Loop to execute receiving of data based on the length.
{
		for(int i=0;i<=length-1;i++)
		{
			while(!(UART0->S1 & 0x20))
			{
			} 								/* wait for receive buffer full */
			*data = UART0_D ; 				// read the char received
			data++;
		}
}

void UART0_IRQHandler(void)
{
	__disable_irq();						//disable interrupt once recieved
	char data;
		if(((UART0_C2 & UART0_C2_TIE_MASK)!=0) && (transbuf->count != 0)){	//check if transmit interrupt is enabled and buffer count is not equal to 0
			data = *(transbuf->head);			
			UART_send(data);												//transmit data
			CB_buffer_remove_item(transbuf/*, &UART0_D*/);					//remove transmitted data
				if(transbuf->count == 0)									
			{
				UART0_C2 &= ~UART0_C2_TIE_MASK;								//disable transmit interrupt
			}
				else
					UART0_C2 |= UART0_C2_TIE_MASK;							//keep transmit interrupt enabled
	   	}
		else if(((UART0_C2 & UART0_C2_RIE_MASK)!=0) && ((UART0_S1 & UART0_S1_RDRF_MASK) !=0)){	//check if receive interrupt is enabled 
	 		uint8_t val = UART_receive();									//read received data
	 		CB_buffer_add_item(recbuf,val);									//add data to receive buffer
	     	//UART0_C2 &= ~UART_C2_RIE_MASK;	
	     	recflag = 1;													//set receive flag
	 	}
	__enable_irq();															//enable interrupt once process for previous interrupt is done
}





