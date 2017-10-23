#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
CB_status CB_init(CB_t *cbuf,uint8_t  length)
{ 
  cbuf->buffer = NULL;
	cbuf->buffer = malloc(sizeof(uint8_t)*length);
	cbuf->length = length;
	cbuf->head = cbuf->buffer;
	cbuf->tail = cbuf->buffer;
	cbuf->count = 0;
  cbuf->peek = 0;
}

CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val)
{ if(!cbuf->tail)
  {
    return Null_pointer;
  }
  if(cbuf->count == cbuf->length)
	{
		return Full;
	}
	*(cbuf->tail) = val;
	if(cbuf->tail==cbuf->buffer+(cbuf->length-1))
	{
		cbuf->tail = cbuf->buffer;
	}
  else
  {
	cbuf->tail++;
  }
	cbuf->count=cbuf->count+1;
}
CB_status CB_buffer_remove_item(CB_t *cbuf)
{	
	if(cbuf->count==0)
	{
		return Empty;		
	}
  *(cbuf->head)=100;
  if(cbuf->head == cbuf->buffer+cbuf->length-sizeof(char))
  {
    cbuf->head = cbuf->buffer;
  }
  else
  {
    cbuf->head++;
  }
  cbuf->count = cbuf->count-1;
  cbuf->status=No_error;
  return cbuf->status;
}

CB_status CB_is_full(CB_t *cbuf)
{
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  if(cbuf->count == cbuf->length)
  {
    cbuf->status = Full;
  }
  else
    cbuf->status = Available;
  return cbuf->status;
}

CB_status CB_is_empty(CB_t *cbuf)
{
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  if(cbuf->count == 0)
  {
    cbuf->status = Empty;
  }
  else
    cbuf->status = Available;
  return cbuf->status;
}

CB_status CB_peek(CB_t *cbuf, uint8_t position)
{ 
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  else if(position > cbuf->length)
  {
    cbuf->status = Wrong_memory_access;
  }
  else if(position > cbuf->count)
  {
    cbuf->status = Empty;
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
    cbuf->status=No_error;
  }
  return (cbuf->status);
}

CB_status CB_destroy(CB_t *cbuf)
{
  free((uint8_t *)cbuf->buffer);
  free(cbuf);
  return No_error;
}
