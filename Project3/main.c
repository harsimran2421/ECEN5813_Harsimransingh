#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"
#include "non_block_logger.h"
#include "binary_logger.h"
#include "conversion.h"
#include "project2.h"
/*Defining buffer lengths*/
uint8_t length_TXbuff=255;
uint8_t length_RXbuff=16;

#ifdef BBB
  #define UART_initialize()
  #define FRDM_log_data(data,length) BBB_log_data(data,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set,length)
  #define FRDM_log_string(data) BBB_log_string(data)
  #define UART0_C2 (replace)
#endif

/*Compile time switch for HOST*/
#ifdef HOST
  #define UART_initialize()
  #define FRDM_log_data(data,length) BBB_log_data(data_TX,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set,length)
  #define FRDM_log_string(data) BBB_log_string(data)
  #define UART0_C2 (replace)
#endif

/*Compile time switch for FRDM*/
#ifdef FRDM
  #include "uart_init.h"
  #include "MKL25Z4.h"
  #define printf(...)
#endif
int main()
{
/*Create log item*/
  system_log = create_log();
/*Create and Initialize Transmit Circular Buffer*/
  transbuf = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(transbuf, length_TXbuff);
  //UART_initialize();
#ifdef LOG_ON
  system_log->logID = LOGGER_INITIALIZED;
  log_item(system_log);
  system_log->logID = SYSTEM_INITIALIZED;
  log_item(system_log);
#endif
/*Create and Initialize Receiver Circular Buffer*/
  recbuf = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(recbuf,length_RXbuff);
#ifdef LOG_ON
/*Testing log_data function*/
  uint8_t payload_string1[18] = "Testing log_data\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 18;
  system_log->Payload = payload_string1;
  log_item(system_log);
  uint8_t test1[4]={'1','2','3','4'};
  uint8_t * data_TX = test1;
  uint8_t length_TX=(sizeof(test1)/sizeof(uint8_t));
  FRDM_log_data(data_TX,length_TX);
  printf("\n");
/*Testing log_string function*/
  uint8_t payload_string2[20] = "Testing log_string\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 20;
  system_log->Payload = payload_string2;
  log_item(system_log);
  uint8_t test2[]="This is a string";
  data_TX=test2;
  FRDM_log_string(data_TX);
  printf("\n");
/*Testing log_integer function*/
  uint8_t payload_string3[21] = "Testing log_integer\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 21;
  system_log->Payload = payload_string3;
  log_item(system_log);
  uint32_t test3=1234;
  length_TX=sizeof((test3)/sizeof(uint8_t));
  FRDM_log_integer(test3,length_TX);
  printf("\n");
  destroy_log(system_log);
  system_log = NULL;
#else
#ifdef HOST
  printf("logging functionality is disabled");
#elif BBB
  printf("logging functionality is disabled");
#else
/*Print when logging is disabled*/
  uint8_t string3[34]=" Logging functionality is disabled";
  uint8_t *str_ptr=string3;
  uint8_t length=0;
  uint8_t state;
  while(*str_ptr!='\0'){
  length++;
  str_ptr++;
}
str_ptr=str_ptr-length;
state = CB_buffer_add_items(transbuf,str_ptr,length);
if(state == NULL_POINTER)
{
  uint8_t nullPointerError[] = "NULL Pointer\n\r";
  system_log->logID = LOG_ERROR;
  system_log->LogLength = 14;
  system_log->Payload = nullPointerError;
  log_item(system_log);
}
UART0_C2|=UART_C2_TIE_MASK;
#endif
#endif
#ifdef FRDM
  while(1)
  {
    if(recflag == 1)
    {
      project2();
    }
  }
#endif
uint8_t val[]="Absdw123ired";
CB_buffer_add_items(recbuf,val,12);
for(uint8_t i=0; i<=10; i++)
{
  project2();
}
}
