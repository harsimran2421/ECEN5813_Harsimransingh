

#include <stdlib.h>
#ifdef FRDM
  #include "MKL25Z4.h"
  #include "uart.h"
#endif
#include "circbuf.h"
#include "project2.h"
#include <stdio.h>
#include <stdint.h>
#include<string.h>
extern CB_t *transbuf;
extern CB_t *recbuf;
extern uint8_t recflag;
int main(void)
{
#ifdef FRDM
uint8_t i = 0;
transbuf = create_buffer(transbuf);
recbuf = create_buffer(recbuf);
uint8_t val = 0;
UART_configure();
uint8_t str[] ="harsimransingh Bindra";
add_to_buffer(str);

UART0_C2 |= UART0_C2_TIE_MASK | UART0_C2_RIE_MASK;
while(1)
{

	if(recflag==1)
	{
		project2();
	}
}
return 0;
#endif
#ifdef HOST
uint8_t i = 0;
recbuf = malloc(sizeof(CB_t));
CB_init(recbuf,10);
char str[10];
#ifdef Project2
while(1)
{
  scanf("%c",&str[i]);
  CB_buffer_add_item(recbuf, str[i]);
	i++;
project2();
#endif
#endif
}
}

