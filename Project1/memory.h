<<<<<<< HEAD
#include <stdio.h>
#include <stdint.h>
uint8_t cal_length(uint8_t *ptr);
uint8_t *my_memmove(uint8_t *src, uint8_t *dst,size_t length);
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst,size_t length);
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value);
uint8_t *my_memzero(uint8_t *src, size_t length);
uint8_t *my_reverse(uint8_t *src, size_t length);
uint32_t *reserve_words(size_t length);
void free_words(uint32_t *src);
=======
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

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdio.h>
#include <stdint.h>
uint8_t cal_length(uint8_t *ptr);                               //Funcation to calculate length of the string
uint8_t *my_memmove(uint8_t *src, uint8_t *dst,size_t length);  //Function to move a data from one location to another
uint8_t *my_memcpy(uint8_t *src, uint8_t *dst,size_t length);   //Function to copy data from one location to another
uint8_t *my_memset(uint8_t *src, size_t length, uint8_t value); //Function to set particular value to all given locations
uint8_t *my_memzero(uint8_t *src, size_t length);               //function to set all values to 0 at given memory locations
uint8_t *my_reverse(uint8_t *src, size_t length);               //Function to reverse data at given memory location
uint32_t *reserve_words(size_t length);                         //function to reserve a particular memory location through dynamic memory allocation
void free_words(uint32_t *src);                                 //Function to free  dynamically allocated memory
#endif
>>>>>>> Changes in header file
