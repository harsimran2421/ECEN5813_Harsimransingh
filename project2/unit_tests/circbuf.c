/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 10/28/2017
 * *
 * * File : circbuff.c
 * * Description : Source file for Circular buffer functions
 * *    CB_status CB_init(CB_t *cbuf,uint8_t  length)
 * *    CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val)
 * *    CB_status CB_buffer_remove_item(CB_t *cbuf)
 * *    CB_status CB_is_full(CB_t *cbuf)
 * *    CB_status CB_is_empty(CB_t *cbuf)
 * *    CB_status CB_peek(CB_t *cbuf, uint8_t position)
 * *    CB_status CB_destroy(CB_t *cbuf)
 * *    
 * ***************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"

/*This function is used to initialize circular buffer, to make head,tail
 * and buffer point at first location of buffer and initialize count to 0*/
CB_status CB_init(CB_t *cbuf,uint8_t  length)
{ 
  cbuf->buffer = NULL;
	cbuf->buffer = malloc(sizeof(uint8_t)*length);
	cbuf->length = length;
	cbuf->head = cbuf->buffer;
	cbuf->tail = cbuf->buffer;
	cbuf->count = 0;
  cbuf->peek = 0;
  return No_error;
}

/*This function is used to add element to circular buffer*/
CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val)
{ if(!cbuf->tail)
  { /*Return null pointer error if Cbuf doesn't point to a valid loaction*/
    return Null_pointer;
  }
  if(cbuf->count == cbuf->length)
	{
    /*Condition to check if buffer is not full*/
		return Full;
	}
	*(cbuf->tail) = val;
  /*Put the data at location pointed by head*/
	if(cbuf->tail==cbuf->buffer+(cbuf->length-1))
	{
    /*Wrap around, if tail is pointing to last location of buffer*/
		cbuf->tail = cbuf->buffer;
	}
  else
  {
	cbuf->tail++;
  }
	cbuf->count=cbuf->count+1;
  /*Return No_error after adding element in buffer*/
  return No_error;
}

/*This function is used to remove elements from circular buffer*/
CB_status CB_buffer_remove_item(CB_t *cbuf)
{	
 if(!cbuf->tail)
  { /*Return null pointer error if Cbuf doesn't point to a valid loaction*/
    return Null_pointer;
  }

	if(cbuf->count==0)
	{
    /*Count value checks if buffer is empty*/
		return Empty;		
	}
  /*After removing the element from buffer, increment tail pointer
   *               and decrement count value*/ 
  *(cbuf->head)=0;
  if(cbuf->head == cbuf->buffer+cbuf->length-sizeof(char))
  {
    /*Wrap around if head points at last location*/
    cbuf->head = cbuf->buffer;
  }
  else
  {
    cbuf->head++;
  }
  cbuf->count = cbuf->count-1;
  cbuf->status=No_error;
  return No_error;
}

/*This function checks if buffer is full*/
CB_status CB_is_full(CB_t *cbuf)
{
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  if(cbuf->count == cbuf->length)
  {
    //If count value is equal to length, return circular buffer is full 
    return Full;
  }
  else
    /*If count is less than length, return circular buffer is available*/
    return Available;
}

/*This function checks if buffer is empty*/
CB_status CB_is_empty(CB_t *cbuf)
{
  if(cbuf == NULL)
  { 
    /*return null pointer error,if Cbuf doesn't point to a valid loaction*/ 
    return Null_pointer;
  }
  if(cbuf->count == 0)
  {
    /*If Count=0, return circular buffer is empty*/
    return Empty;
  }
  else
    /*If count!=0 return buffer is available*/
    return Available;
}

/*This function is used to check the value present at a particular
 *   location of circular buffer*/
CB_status CB_peek(CB_t *cbuf, uint8_t position)
{ 
  if(cbuf == NULL)
  {
    /*Return null pointer error, if CircbuffTR doesn't point to a valid location*/
    return Null_pointer;
  }
  else if(position > cbuf->length)
  {
    return Wrong_memory_access;
  }
  else if(position > cbuf->count)
  {
    return Empty;
  }
  else
  {
    volatile uint8_t *pos = cbuf->head;
    while(position)
    {  
      if(pos == cbuf->buffer+cbuf->length-sizeof(uint8_t))
      {
        pos = cbuf->buffer;
      }
      else
      {
        pos = pos+1;
      }
      position--;
    }
    cbuf->peek = *pos;
  }
  return No_error;
}

/*This function is used to free the heap memory allocate to buffer*/
CB_status CB_destroy(CB_t *cbuf)
{
  free((uint8_t *)cbuf->buffer);
  free(cbuf);
  /*After destroying memory return no error*/
  return No_error;
}
