#include <stdio.h>
#include <stdint.h>
#include "debug.h"                                 //invokes the user defined library for debugging
void print_memory(uint8_t *start, uint32_t length)
{	uint8_t i = 0;
  for(i = 0; i<length; i++)                       //to print data at given memory locations
	{
		printf("%X/n", *start);
		start++;
	}
}
