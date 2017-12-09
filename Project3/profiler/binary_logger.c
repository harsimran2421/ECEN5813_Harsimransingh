/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 11/23/2017
 * *
 * * File : bonary_logger.c
 * * Description : Header file for Binary logger functions
 * *               -void FRDM_log_data(uint8_t * data_TX,uint8_t length_TX)
 * *               -void log_flush(void)
 * *               -void BBB_log_data(uint8_t * data_TX,uint8_t length_TX)
 * *               -void FRDM_log_string(uint8_t * data_TX)
 * *               -void BBB_log_string(uint8_t * data_TX)
 * *               -void FRDM_log_integer(uint32_t set,uint8_t length)
 * *               -void BBB_log_integer(uint32_t set,uint8_t length)
* **************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "circbuf.h"
//#include "memory.h"
#include "binary_logger.h"
//#include "conversion.h"
//#include "non_block_logger.h"
#include "FRDM.h"
extern CB_t *transbuf;
extern CB_t *recbuf;
#ifdef HOST
#define UART0_C2 replace
#define UART0_C2_TIE_MASK 0
#endif

#ifdef BBB
#define UART0_C2 replace
#define UART0_C2_TIE_MASK 0
#endif

#ifdef FRDM
#include "uart.h"
#include "MKL25Z4.h"
#endif

uint8_t replace;

/*This function is used as to add data to circular buffer and then transmit through uart
 *  for FRDM*/
void FRDM_log_data(uint8_t * data,uint8_t length)
{
  CB_buffer_add_items(transbuf,data,length);
  UART0_C2 |= UART0_C2_TIE_MASK;                     //To Enable the transmitting interrupt for UART
}

void FRDM_log_string(uint8_t * data)
{
  uint8_t length=0;
  while(*data!='\0')                                //To calculate the length of input string
  {
    length++;
    data++;
  }
  data=data-length;
  CB_buffer_add_items(transbuf,data, length);
  UART0_C2|=UART0_C2_TIE_MASK;
}

void FRDM_log_integer(uint32_t set, uint8_t length)
{
  uint32_t base=10;
  uint8_t test_set[length];
  uint8_t *str=test_set;
  length=my_itoa(set,str,base);                   //Function to convert integer to ascii
  CB_buffer_add_items(transbuf,str,length);
  UART0_C2|=UART0_C2_TIE_MASK;                     //To enable transmit interrupt
}

void BBB_log_data(uint8_t * data,uint8_t length)
{
  CB_buffer_add_items(transbuf,data,length);
  while(transbuf->count!=0)
  {
    printf("%c ",*(transbuf->head));
    CB_buffer_remove_item(transbuf);
  }
}

void BBB_log_integer(uint32_t set,uint8_t length)
{
  uint32_t base=10;
  uint8_t test_set[length];
  uint8_t *str=test_set;
  length=my_itoa(set,str,base);                  //Function to convert integer to ascii
  CB_buffer_add_items(transbuf,str,length);
  while(transbuf->count)
  {
    printf("%c ",*(transbuf->head));
    CB_buffer_remove_item(transbuf);
  }
}
void BBB_log_string(uint8_t * data)
{
  uint8_t length=0;
/*To calculate length of string*/
  while(*data!='\0')
  {
    length++;
    data++;
  }
  data=data-length;
  CB_buffer_add_items(transbuf, data, length);
  //transbuf->count = transbuf->count - 1;
  while(transbuf->count)
  {
    printf("%c ",*(transbuf->head));
    CB_buffer_remove_items(transbuf,1);
  }  
}

/*This function is used to block until logger buffer is empty*/
//void log_flush(void)
//{
//  while(transbuf->count)                        //Checks count value to check is buffer is empty
//  {
//    system_log->logID= SYSTEM_HALTED;           //Binary logger for system halted
//    system_log->LogLength=0;
//    log_item(system_log);
//  }
//}

