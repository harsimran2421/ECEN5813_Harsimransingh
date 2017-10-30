#include <stdint.h>
#include<stdlib.h>
#include "circbuf.h"
#include "uart.h"
#include "conversion.h"

extern CB_t *recbuf;
extern uint8_t recflag;
uint32_t alpha_Count = 0;
uint32_t num_Count = 0;
uint32_t punc_Count = 0;
uint32_t misc_Count = 0;
uint32_t rec_DataCount = 0;

void project2()
{
	uint8_t rec_data=0;
	if(recbuf->count == 0)
	{
		return Empty;
	}
	else
	{
        rec_data = *(recbuf->head);
		if((rec_data>='a' && rec_data<='z') || (rec_data>='A' && rec_data<='Z'))
		{
			alpha_Count++;
			rec_DataCount++;
		}
		else if(rec_data>='0' && rec_data<='9')
		{
			num_Count++;
			rec_DataCount++;
		}
		else if (rec_data == '.' || rec_data == ',' || rec_data == '\'' || rec_data == ':' || rec_data == ';' || rec_data == '!' || rec_data == '"')
		{
		punc_Count++;
		rec_DataCount++;
		}
		else
		{
		misc_Count++;
		rec_DataCount++;
		}
		}
		CB_buffer_remove_item(recbuf);
	if(rec_DataCount == 10 || rec_data == 13)
	{
#ifdef FRDM
		uint8_t *data = NULL;
		data = malloc(sizeof(uint32_t));
		uint32_t length = 0;
		uint8_t alphastring[]= "\n\rNo of Alphabets:";
    UART_send_n(alphastring, 20);
		length=my_itoa(alpha_Count, data, 10);
		UART_send_n(data, length);
#endif

#ifdef HOST
printf("No of Alphabets are:%d\n",alpha_Count);
#endif

#ifdef FRDM
		uint8_t Numstring[]= "\n\rNo of Numbers:";
    UART_send_n(Numstring, 18);
		length = my_itoa(num_Count, data, 10);
		UART_send_n(data, length);
#endif

#ifdef HOST
printf("No of Numbers are:%d\n",num_Count);
#endif

#ifdef
		uint8_t Punstring[]= "\n\rNo of puncuations:";
    UART_send_n(Punstring, 22);
		length=my_itoa(punc_Count, data, 10);
		UART_send_n(data, length);
#endif
#ifdef HOST
printf("No of puncuations are:%d\n",punc_Count);
#endif

#ifdef FRDM
		uint8_t miscstring[]= "\n\rNo of Miscellaneous characters:";
		UART_send_n(miscstring, 35);
		length=my_itoa(misc_Count, data, 10);
		UART_send_n(data, length);
#endif

#ifdef HOST
printf("No of Miscelenous items are:%d\n",misc_Count);
#endif

		rec_DataCount =0;
  #ifdef FRDM
		free(data);
  #endif
	}
	recflag = 0;
}





