<<<<<<< HEAD
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);
int8_t big_to_little32(uint32_t *data, uint32_t length);
int8_t little_to_big32(uint32_t *data, uint32_t length);

=======
/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/01/2017
 * *
 * *   File: conversion.h
 * *
 * *   Description: Header file for data manipulation 
 * *     -my_itoa
 * *     -my_atoi
 * *     -dump_memory
 * *     -big_to_little32
 * *     -little_to_big32
 * *
 * *
 * ********************************************************
 header  file for function called "conversion"*/

#ifndef CONERSION_H_
#define CONVERSION_H_
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);   //Function converting integral values to strings
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base); //Function converting string ascii inputs to integers
int8_t big_to_little32(uint32_t *data, uint32_t length);      //Changing endianness from big endian to little endian
int8_t little_to_big32(uint32_t *data, uint32_t length);      //Changing endianness from little endian to big endian
#endif
>>>>>>> Changes in header file
