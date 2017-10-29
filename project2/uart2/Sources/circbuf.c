/*
 * circbuf.c
 *
 *  Created on: Oct 28, 2017
 *      Author: harsi
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
CB_status CB_init(CB_t **cbuf,uint8_t  length)
{
	CB_t *temp = *cbuf;
	temp->buffer = NULL;
	temp->buffer = malloc(sizeof(uint8_t)*length);
	temp->length = length;
	temp->head = temp->buffer;
	temp->tail = temp->buffer;
	temp->count = 0;
	temp->peek = 0;
	*cbuf=temp;
  return No_error;
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
	cbuf->count++;
  return No_error;
}
CB_status CB_buffer_remove_item(CB_t *cbuf /*uint8_t *value*/)
{
	if(cbuf->count==0)
	{
		return Empty;
	}
//	*value = *(cbuf->tail);
  *(cbuf->head)=100;
  if(cbuf->head == cbuf->buffer+cbuf->length-sizeof(uint8_t))
  {
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

CB_status CB_is_full(CB_t *cbuf)
{
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  if(cbuf->count == cbuf->length)
  {
    return Full;
  }
  else
    return Available;
}

CB_status CB_is_empty(CB_t *cbuf)
{
  if(cbuf == NULL)
  {
    return Null_pointer;
  }
  if(cbuf->count == 0)
  {
  return Empty;
  }
  else
    return Available;
}

CB_status CB_peek(CB_t *cbuf, uint8_t position)
{
  if(cbuf == NULL)
  {
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
    volatile uint8_t *pos = cbuf->tail;
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

CB_status CB_destroy(CB_t *cbuf)
{
  free((uint8_t *)cbuf->buffer);
  free(cbuf);
  return No_error;
}


