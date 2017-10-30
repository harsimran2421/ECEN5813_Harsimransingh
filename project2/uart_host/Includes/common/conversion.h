

#ifndef INCLUDES_CONVERSION_H_
#define INCLUDES_CONVERSION_H_
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

typedef enum conversion_status{
  Invalid_pointer,
  Pass,
  Fail
}conversion_status_t;

uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);
/**
 * Function converting integral values to strings
 *
 * This function takes an integer value as input and converts it into a string and handles both the signed and unsigned data.
 * It handles number from base 2 to base 16
 *
 * returns uint8_t*/
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);
/**Function converting string ascii inputs to integers
 *
 * This function takes a string as input and converts it into a integer value and handles both the signed and unsigned data.
 * It handles number from base 2 to base 16
 *
 * returns uint8_t*/
int8_t big_to_little32(uint32_t *data, uint32_t length);
/**
 * Changing endianness from big endian to little endian
 *
 * This function takes data which is saved in big endian format and changes the endianness to little endian.
 * This function is used when the data needs to be transfered to different platforms with different endianness
 *
 * returns int8_t*/
int8_t little_to_big32(uint32_t *data, uint32_t length);
/**
 *Changing endianness from little endian to big endian
 *
 * This function takes data which is saved in little endian format and changes the endianness to big endian.
 * This function is used when the data needs to be transfered to different platforms with different endianness
 *
 * returns int8_t*/

#endif /* INCLUDES_CONVERSION_H_ */
