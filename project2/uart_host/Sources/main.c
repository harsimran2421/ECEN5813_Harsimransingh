

#include <stdlib.h>
#ifdef FRDM
#include "MKL25Z4.h"
#endif
#include "uart.h"
#include "circbuf.h"
#include "project2.h"

#ifdef FRDM
extern CB_t *transbuf;
extern CB_t *recbuf;
extern uint8_t recflag;
int main(void)
{
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
}
#endif

#ifdef HOST
int main(void)
{
recbuf = create_buffer(recbuf);
uint8_t str[50];
while(1)
gets(str);
while(str[i]!='\0')
{
	CB_buufer_add_item(recbuf, str[i])
	i++:
}
#ifdef project2
	project2();
#endif
}
}
