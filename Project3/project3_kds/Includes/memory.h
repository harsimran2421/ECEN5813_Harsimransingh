#ifndef INCLUDES_MEMORY_H_
#define INCLUDES_MEMORY_H_
/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/01/2017
 * *
 * *   File: memory.h
 * *
 * *   Description: Header file for data manipulation
 * *    -cal_length
 * *    -my_memmove
 * *    -my_memcpy
 * *    -my_memset
 * *    -my_memzero
 * *    -my_reverse
 * *    -reserve_words
 * *    -free_words
 * *
 * *
 * ********************************************************
 header for function called "memory"*/

#include <stdio.h>
#include <stdint.h>

typedef enum status_memory{
  Pass,
  Invalid_pointer,
  Fail
  }memory_status_t;

uint8_t cal_length(uint8_t *ptr);
/**
 * Function to calculate length of the string
 *
 *This function calculates the length of the string which is stored at the memory location pointed by the pointer passed
 *
 * returns uint8_t(length)*/

uint8_t my_memmove(uint8_t *src, uint8_t *dst,size_t length);
/**
 * Function to move a data from one location to another
 *
 * This function is used to move data from one memory location to another.
 * overlapping of the two memory locations is checked and handled accordingly
 *
 * returns uint8_t*/
uint8_t my_memcpy(uint8_t *src, uint8_t *dst,size_t length);
/**
 * Function to copy data from one location to another
 *
 * This function is used to copy data from one memory location to another
 * This function does not handle overlapping and data may be overwritten
 *
 * returns uint8_t*/
uint8_t my_memset(uint8_t *src, size_t length, uint8_t value);
/**
 * Function to set particular value to all given locations
 *
 * This function sets a particular value given as parameter to all given memory locations.
 *
 * returns uint8_t*/
uint8_t my_memzero(uint8_t *src, size_t length);
/**
 * function to set all values to 0 at given memory locations
 *
 * This function is a more specific version of memset function, it sets the value to 0 for all the memory location given
 *
 * returns uint8_t*/
uint8_t my_reverse(uint8_t *src, size_t length);
/**
 * Function to reverse data at given memory location
 *
 * This function reverses a particular array or a given string using pointer arithematic
 *
 * returns uint8_t*/
uint32_t *reserve_words(size_t length);
/**
 * function to reserve a particular memory location through dynamic memory allocation
 *
 * This function dynamically allocates memory to the pointer passed as the parameter
 *
 * returns uint32_t* */
void free_words(uint32_t *src);
/**
 * Function to free  dynamically allocated memory
 *
 * This function frees the memory which was dynamically allocated for the function. It avoids the memory exhaustion
 *
 * returns void */


#endif /* INCLUDES_MEMORY_H_ */
