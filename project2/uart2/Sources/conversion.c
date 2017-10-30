/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/01/2017
 * *
 * *   File: conversion.c
 * *
 * *   Description: source file for data manipulation
 * *     -my_itoa
 * *     -my_atoi
 * *     -big_to_little32
 * *     -little_to_big32
 * *
 * *
 * ********************************************************/

#include <stdint.h>
#include <stdio.h>
#include "conversion.h"                                     //invokes user defined header file for conversion
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base)  //function to convert integers to ascii strings
{
	uint8_t rem, i, temp, digits, count = 0;
  uint8_t sign = 0;
	uint8_t *last;
	if(data<0)                                                //checks if data is negative and appends - to the string
	{
  	data = -data;
		*ptr = '-';
		ptr++;
		count++;
		sign++;					                                          //to check the sign of the input
	}
  if(data==0)
	{						                                                //to return zero  value if zero is entered
		*ptr='0';
		digits=1;
		return digits;
	}
	while(data != 0)
	{
		if((rem = data%base) > 9)                                 //condition if there is hex conversion
		{
			*ptr=('A'+ rem-10);                                     //adds the ascii value of 'A' character to remainder
		}
		else
		{
			*ptr=rem + '0';                                        //for normal conversion adds the ascii value of '0' to the remainder
		}
		data = data/base;
		ptr++;
		count++;
		}
  *ptr = '\0';
  last = ptr-sizeof(uint8_t);
    digits = count;
if(sign ==1)
{
	ptr = ptr - sizeof(uint8_t)*(count-1);
}
else
{
	ptr = ptr - sizeof(uint8_t)*(count);
}
if(count%2 !=0)                                             //to check the string length whether its even or odd
{
	count =count-1;
}
for(i=0; i<(count/2); i++)                                  //to reverse the string and store the ascii string in correct order
{
	temp = *last;
	*last = *ptr;
	*ptr = temp;
	ptr++;
	last--;
}
ptr = ptr - sizeof(uint8_t)*(count/2);
return digits;
}

int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base)//function to convert ascii strings to integers
{
  if(ptr == NULL)
  {
    return Invalid_pointer;
  }
	int32_t integer=0;
	uint8_t i, sign=0;
	if(*ptr == '-')                                           //to check whether the first character is '-' and set the sign bit accordingly
	{
    sign++;
		ptr++;
    digits = digits-1;
	}
	for(i = 0; i<digits; i++)                                 //to convert ascii strings to integers
	{
		if('0' <= *ptr && *ptr <='9')
		{
			integer = integer*base + *ptr - '0';                  //subtracts the
			ptr++;
		}
		else
		{
			integer = integer*base + *ptr -55;
			ptr++;
		}
	}
	if (sign == 1)                                           // to assign the proper sign to the integer according to the sign value
	{
		integer = -integer;
	}
	return integer;
}

int8_t big_to_little32(uint32_t *data, uint32_t length)   //to change the endianness from big to little
{
  if(data == NULL)
  {
    return Invalid_pointer;
  }
	uint32_t temp, temp1, temp2, temp3;
	temp = *data & 0XFF000000;                              //masking all but msb
	temp1 = *data & 0X000000FF;
	temp2 = *data & 0X00FF0000;
	temp3 = *data & 0X0000FF00;
	temp = temp >> 24;                                      //shifting msb to lsb
	temp1 = temp1<<24;
	temp2 = temp2>>8;
	temp3 = temp3<<8;
	*data = temp | temp1 | temp2 | temp3;                   //assembles all bytes after proper shifting and getting the required endianness
  return Pass;
}

int8_t little_to_big32(uint32_t *data, uint32_t length)   //to change the endianness from little to big
{
  if(data == NULL)
  {
    return Invalid_pointer;
  }
	uint32_t temp, temp1, temp2, temp3;
	temp = *data & 0XFF000000;                              //masking the lsb
	temp1 = *data & 0X000000FF;
	temp2 = *data & 0X00FF0000;
	temp3 = *data & 0X0000FF00;
	temp = temp >> 24;                                      //shifting the lsb
	temp1 = temp1<<24;
	temp2 = temp2>>8;
	temp3 = temp3<<8;
	*data = temp | temp1 | temp2 | temp3;                   //assembles all the bytes after proper shifting to get the required endianness
  return Pass;
}





