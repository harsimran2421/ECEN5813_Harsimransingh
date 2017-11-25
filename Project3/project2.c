#include <stdint.h>
#include<stdlib.h>
#include "circbuf.h"
#include "conversion.h"
#include "memory.h"
#include "binary_logger.h"
#include "non_block_logger.h"
#include "project2.h"
#ifdef BBB
  #define UART_initialize()
  #define FRDM_log_data(data,length) log_data_BBB(data,length)
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
uint16_t rec_DataCount = 0;

void project2(void)
{
	uint8_t rec_data=0;
	if(recbuf->count == 0)
	{
		//return Empty;
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
    recbuf->head++;
		}
  if(rec_DataCount == 1)
  {
    system_log = create_log();
    system_log->logID = DATA_ANALYSIS_STARTED;
    system_log->LogLength = 0;
    log_item(system_log);
    destroy_log(system_log);
  }
	if(rec_DataCount == 10 || rec_data == 13)
	{ uint8_t ret[]="\n\r";
		uint8_t alphastring[]= "No of Alphabets:";
    FRDM_log_data(ret, 2);
		FRDM_log_data(alphastring, 16);
    system_log->logID = DATA_ALPHA_COUNT;
    if(alpha_Count>9)
      system_log->LogLength = 2;
    else 
      system_log->LogLength = 1;
      my_itoa(alpha_Count, (uint8_t*)&alpha_Count, 10);
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
		system_log->Payload = (uint8_t*)&punc_Count;
    log_item(system_log);
    punc_Count=0;

    uint8_t miscstring[]= "No of Miscellaneous characters:";
    FRDM_log_data(ret, 2);
		FRDM_log_data(miscstring, 33);
		
    system_log->logID = DATA_MISC_COUNT;
    if(misc_Count>9)
      system_log->LogLength = 2;
    else
      system_log->LogLength = 1;
    my_itoa(misc_Count,(uint8_t*)&misc_Count, 10);
		system_log->Payload = (uint8_t*)&misc_Count;
    log_item(system_log);
    misc_Count=0;

    CB_buffer_remove_items(recbuf, rec_DataCount);
		rec_DataCount =0;
	}
	recflag = 0;
}

