#include <stdint.h>
#include<stdlib.h>
#include "circbuf.h"
#include "conversion.h"
#include "memory.h"
#include "binary_logger.h"
#include "non_block_logger.h"
#include "project2.h"
#include "FRDM.h"
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
  #define FRDM_log_data(data,length) BBB_log_data(data,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set,length)
  #define FRDM_log_string(data) BBB_log_string(data)
  #define UART0_C2 (replace)
#endif

/*Compile time switch for FRDM*/
#ifdef FRDM
  #include "uart.h"
  #include "MKL25Z4.h"
  #define printf(...)
#endif
uint16_t replace=0;
uint16_t alpha_Count = 0;
uint16_t num_Count = 0;
uint16_t punc_Count = 0;
uint16_t misc_Count = 0;

void project2(void)
{
	if(recbuf->count == 0)
	{
		//return Empty;
	}
	else
	{
		if((rec_data>='a' && rec_data<='z') || (rec_data>='A' && rec_data<='Z'))
		{
			alpha_Count++;
		}
		else if(rec_data>='0' && rec_data<='9')
		{
			num_Count++;
		}
		else if (rec_data == '.' || rec_data == ',' || rec_data == '\'' || rec_data == ':' || rec_data == ';' || rec_data == '!' || rec_data == '"')
		{
		punc_Count++;
		}
		else
		{
		misc_Count++;
		}
		}
  if(rec_DataCount == 1)
  {
    //system_log = create_log();
    system_log->logID = DATA_ANALYSIS_STARTED;
    system_log->LogLength = 0;
    log_item(system_log);
    //destroy_log(system_log);
  }
  if(rec_data==32)
  {
	  heart_off=1;
  }
  if(rec_data==61)
  {
	  heart_off=0;
  }
  if(rec_data==91)
  {
	  log_off=1;
  }
  if(rec_data==93)
  {
	  log_off=0;
  }
	if(rec_DataCount == 10 || rec_data == 13)
	{ 
    uint8_t ret[]="\n\r";
		uint8_t alphastring[]= "No of Alphabets:";
    FRDM_log_data(ret, 2);
		FRDM_log_data(alphastring, 16);
    system_log->logID = DATA_ALPHA_COUNT;
    if(alpha_Count>9)
      system_log->LogLength = 2;
    else 
      system_log->LogLength = 1;
      my_itoa(alpha_Count, (uint8_t*)&alpha_Count, 10);
      FRDM_log_data((uint8_t*)&alpha_Count,system_log->LogLength);
      system_log->Payload = (uint8_t*)&alpha_Count;
      log_item(system_log);
      alpha_Count=0;
		  
		uint8_t Numstring[]= "No of Numbers:";
    FRDM_log_data(ret, 2);
		FRDM_log_data(Numstring, 14);
		system_log->logID = NUMERIC_COUNT;
    if(num_Count>9)
      system_log->LogLength=2;
    else
      system_log->LogLength=1;
    my_itoa(num_Count, (uint8_t*)&num_Count, 10);
    FRDM_log_data((uint8_t*)&num_Count,system_log->LogLength);
    system_log->Payload = (uint8_t*)&num_Count;
    log_item(system_log);
    num_Count=0;
    

    uint8_t Punstring[]= "No of puncuations:";
		FRDM_log_data(ret, 2);
    FRDM_log_data(Punstring, 18);
		system_log->logID = DATA_PUNCTUATION_COUNT;
    if(punc_Count>9)
      system_log->LogLength = 2;
    else
      system_log->LogLength = 1;
    my_itoa(punc_Count,(uint8_t*)&punc_Count, 10);
		FRDM_log_data((uint8_t*)&punc_Count,system_log->LogLength);
    system_log->Payload = (uint8_t*)&punc_Count;
    log_item(system_log);
    punc_Count=0;

    uint8_t miscstring[]= "No of Miscellaneous characters:";
    FRDM_log_data(ret, 2);
		FRDM_log_data(miscstring, 31);
		my_itoa(misc_Count,(uint8_t*)&misc_Count, 10); 
    system_log->logID = DATA_MISC_COUNT;
    if(misc_Count>9)
      system_log->LogLength = 2;
    else
      system_log->LogLength = 1;
    FRDM_log_data((uint8_t*)&misc_Count,system_log->LogLength);
    system_log->Payload = (uint8_t*)&misc_Count;
    log_item(system_log);
    misc_Count=0;
    for(uint8_t i=0; i<rec_DataCount;i++)
    {
    	FRDM_log_data((uint8_t *)recbuf->head, 1);
    	CB_buffer_remove_items(recbuf, 1);
    }
    system_log->logID = DATA_ANALYSIS_COMPLETED;
    system_log->LogLength = 0;
    log_item(system_log);
	rec_DataCount =0;
	//destroy_log(system_log);
	}
	recflag = 0;
}

