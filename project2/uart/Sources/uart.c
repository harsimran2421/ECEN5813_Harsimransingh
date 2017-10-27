#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include <MKL25Z4.H>

// MYCODE
int UART_configure(void)
{
	SIM_SCGC4 |= 0x400; /* enable clock for UART0 */
	SIM_SOPT2 |= 0x4000000; /* use FLL output for UART Baud rate generator*/
	UART0->C2 = 0;
	SIM_SCGC5 |= 0x0200; /* enable clock for PORTA */
	PORTA->PCR[2] = 0x0200;
}

int UART_send(char *data_send)
{
	while (1)
	{
		while(!(UART0->S1 & 0x80))
		{
		} /* wait for transmit buffer empty */
	UART0->D = *data_send;
	}
}

int UART_send_n(char *data_send_n, int length)
{
	while (1)
	{
		{for (int i=0;i<=length-1;i++)
			while(!(UART0->S1 & 0x80))
			{
			} /* wait for transmit buffer empty */
		UART0->D = *data_send_n;
		data_send_n++;
		}
	}
}

int UART_receive(char *data_receive)
{	char c;
	while (1)
	{
		while(!(UART0->S1 & 0x20))
		{
		} /* wait for receive buffer full */
	*data_receive = UART2->D ; /* read the char received */

	}
}

int UART_receive_n(char *data_receive_n,int length)
{
	char c;
	while (1)
	{
		for(int i=0;i<=length-1;i++)
		{while(!(UART0->S1 & 0x20))
		{
		} /* wait for receive buffer full */
	*data_receive_n = UART2->D ; /* read the char received */
	data_receive_n++;
		}
	}
}
