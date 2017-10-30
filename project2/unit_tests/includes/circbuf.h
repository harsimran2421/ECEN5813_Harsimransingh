/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 10/28/2017
 * *
 * * File : circbuff.h
 * * Description : header files for Circular buffer functions
 * *    CB_status CB_init(CB_t *cbuf,uint8_t  length)
 * *    CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val)
 * *    CB_status CB_buffer_remove_item(CB_t *cbuf)
 * *    CB_status CB_is_full(CB_t *cbuf)
 * *    CB_status CB_is_empty(CB_t *cbuf)
 * *    CB_status CB_peek(CB_t *cbuf, uint8_t position)
 * *    CB_status CB_destroy(CB_t *cbuf)
 * *    
 * ***************************************************************************/

#include <stdint.h>

/*Enum used for returning the buffer state*/
typedef enum CB_Enum_t{
No_error=1,
Full,
Empty,
Available,
Null_pointer, 
No_length, 
Buffer_allocation_failure,
Wrong_memory_access,
Error
}CB_status;

/*Circular buffer structure*/
typedef struct circular
{
	volatile uint8_t *buffer;
	volatile uint8_t *tail;
	volatile uint8_t *head;
	volatile uint8_t val;
	volatile uint8_t count;
	volatile uint8_t length;
  volatile uint8_t peek;
  CB_status status;
}CB_t;

/******************************************************************************
 * * This function is used to add elements to circular buffer
 * * The return value can be full or available
 * * CB_t *cbuf - Pointer which points to circular buffer
 * * uint8_t val - data to be stored on buffer
 *********************************************************************************/
CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val);

void memcopy(uint8_t *tail, uint8_t val);

/*******************************************************************************
 * * This function is used to allocate heap memory to circular buffer
 * * CB_t *cbuf - pointer which points to the circular buffer
 * * uint8_t length - This variable gives the length of circular buffer
 * *******************************************************************************/
CB_status CB_init(CB_t *cbuf,uint8_t  length);

/*******************************************************************************
 * * This function is used to remove elements from circular buffer
 * * The return value can be empty or available depending on count value
 * * CB_t *cbuf - Pointer which points to circular buffer
 *        *******************************************************************************/
CB_status CB_buffer_remove_item(CB_t *cbuf);

/******************************************************************************
 * * This function is used to check if circular buffer is full
 * * The return value can be full or available depending on count value
 * * CB_t *cbuf - Pointer which points to circular buffer
 * *******************************************************************************/
CB_status CB_is_full(CB_t *cbuf);

/*******************************************************************************
 * * This  function is used to check if circular buffer is empty
 * * The return value can be empty or available depending on count value
 * * CB_t *cbuf - Pointer which points to circular buffer
 * *******************************************************************************/
CB_status CB_is_empty(CB_t *cbuf);

/*******************************************************************************
 * * This function is to check the value at a particular location of buffer
 * * It returns the value present at that loaction
 * * CB_t* cbuf - Pointer which points to circular buffer
 * * uint8_t position - position to look for
 ********************************************************************************/ 
CB_status CB_peek(CB_t *cbuf, uint8_t position);

/******************************************************************************
 * * This function is used to free the heap memory allocated to circular buffer
 * * CB_t *cbuf - Pointer which points to circular buffer
 * ******************************************************************************/
CB_status CB_destroy(CB_t *cbuf);

