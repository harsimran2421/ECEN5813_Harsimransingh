/************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 11/25/2017
 * *
 * * File : non_block_logger.c
 * * Description : Source file for binary logger
 * *               -create_log()
 * *               -log_item()
 * *               -destroy_log()
 * *************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "circbuf.h"
#include "non_block_logger.h"
#include "binary_logger.h"
#include "conversion.h"

/*Compile time switch to include libraries for FRDM*/
#ifdef FRDM
#include "uart.h"
#include "MKL25Z4.h"
#include "RTC.h"
#endif

#if defined BBB || defined HOST
  uint8_t *ctime_string;
  //struct timeval tv;
  time_t current_time;
  #define FRDM_log_data(data,length) BBB_log_data(data,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set, length)
  #define FRDM_log_string(data) BBB_log_string(data)
#endif
uint8_t logString[9] = " Log ID:";
uint8_t payloadString[9]= " Payload:";
uint8_t timestampString[11] = " Timestamp:";

LOG_t * create_log()
{
  LOG_t * ptr = (LOG_t *) calloc(1,sizeof(LOG_t));
  return ptr;
}

uint8_t log_item(LOG_t * ptr)
{
  uint8_t len = ptr->LogLength;
  uint16_t ID = ptr->logID;
  FRDM_log_string("\n\r");
  FRDM_log_string(timestampString);
  #if defined BBB || defined HOST
   // gettimeofday(&tv, NULL);
   current_time=time(NULL);
    ptr->Timestamp = current_time;   
  ctime_string = ctime((time_t*)&current_time);
  #endif
#ifdef FRDM
  ctime_string = ctime((time_t*)&ptr->Timestamp);
#endif
  uint8_t length = strlen(ctime_string);
  ctime_string[length-1] = ' ';
  FRDM_log_string(ctime_string);
  FRDM_log_string(logString);
  if(ID >=0xa)
  {
    my_itoa((uint32_t)ptr->logID,(int8_t*)&(ptr->logID),10);
    FRDM_log_data((uint8_t*)&(ptr->logID),2);
  }
  else
  {
   my_itoa((uint32_t)ptr->logID, (int8_t *)&(ptr->logID),10);
   FRDM_log_data((uint8_t*)&(ptr->logID),1);
  }
  if(len!=0)
  {
    FRDM_log_data((uint8_t * )&payloadString,9);
    FRDM_log_data((ptr->Payload),len);
  }
  return NO_ERROR;
}

uint8_t destroy_log(LOG_t *ptr)
{
  free(ptr);
  return NO_ERROR;
}
