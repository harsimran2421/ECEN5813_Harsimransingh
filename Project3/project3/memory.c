/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/01/2017
 * *
 * *   File: memory.c
 * *
 * *   Description: source file for data manipulation
 * *    -my_memmove
 * *    -my_memcpy
 * *    -my_memset
 * *    -my_memzero
 * *    -my_reverse
 * *    -reserve_words
 * *    -free_words
 * *
 * *
 * ********************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

uint8_t my_memmove(uint8_t *src, uint8_t *dst, size_t length) //function to move data from one memory location to another
{
  if(src == NULL || dst == NULL)
  {
    return Invalid_pointer;
  }
	uint8_t i = 0;
  if((src+sizeof(uint8_t)*length)>=dst && src<dst)            //Checks for overlapping of memory location
	{
   src =  src+(sizeof(uint8_t)*(length-1));
   dst =  dst+(sizeof(uint8_t)*(length-1));
	for(i = 0; i<length; i++)                                   //to move data to the destination memory location
	{
		*dst = *src;
		src--;
		dst--;
  }
  return Pass;
  }
  else
  {
	for(i = 0; i<length; i++)
	{
		*dst = *src;
		src++;
		dst++;
	}
  }
  return Pass;
}

uint8_t my_memcpy(uint8_t *src, uint8_t *dst, size_t length)  //function to copy data from one memory location to another
{
  if(src == NULL || dst == NULL)
  {
    return Invalid_pointer;
  }
	uint8_t i = 0;
  for(i = 0; i<length; i++)                                   //to copy data from source memory address to destination memory location
	{
		*dst = *src;
		src++;
		dst++;
	}
	return Pass;
}

uint8_t my_memset(uint8_t *src, size_t length, uint8_t value)//to set all given memory locations with a particular value
{
  if(src == NULL)
  {
    return Invalid_pointer;
  }
  size_t i = length;
	while(i != 0)                                               //to set a particular value
	{
		*src = value;
		i--;
		src++;
	}
	src = src-(sizeof(uint8_t)*length);
	return Pass;

}

uint8_t my_memzero(uint8_t *src, size_t length)             //function to set all values at given memory locations to zero
{
  if(src == NULL)
  {
    return Invalid_pointer;
  }
  size_t i = length;
	while(i != 0)
	{
		*src = 0;                                                //sets all values to zero
		i--;
		src++;
	}
	src = src-(sizeof(uint8_t)*length);
	return Pass;
}

uint8_t my_reverse(uint8_t *src, size_t length)            //function to reverse a string
{
  if(src == NULL)
  {
    return Invalid_pointer;
  }
  uint8_t *last;
	uint8_t temp,i;
	last = src + sizeof(uint8_t)*length-1;
	if(length%2 != 0)                                         //to check whether the length of the string or number of values are even or odd
	{
		length = length-1;
	}
	for(i = 0; i<(length/2); i++)                             //to reverse the string at given memory location
	{
		temp = *src;
		*src = *last;
		*last = temp;
		src++;
		last--;
	}
	src = src - (sizeof(uint8_t)*(length/2));
	return Pass;
}

uint32_t *reserve_words(size_t length)
{
  uint32_t *reserve = malloc(sizeof(uint32_t)*length);
  return reserve;
}

void free_words(uint32_t *src)                            //function to free the dynamically allocated memory
{
  free(src);
}





