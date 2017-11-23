/**************************************************
 * * Authors : Harsimransingh, Smitesh Modak
 * * Date : 11/22/2017
 * *
 * * File : DMA.h
 * * Description : Header file for configuration of DMA
 * *               -Initialize_dma()
 * *               -memmove_dma_1_byte()
 * *               -memmove_dma_2_byte()
 * *               -memmove_dma_4_byte()
 * *               -memzero_dma_1_byte()
 * *               -memzero_dma_2_byte()
 * *               -memzero_dma_4_Byte()
 * *
 * ***************************************************/
#include "circbuff.h"
#ifndef DMA_H_
#define DMA_H_


/****************************************************************
 * * Initialize_dma() - This function selects the clock for dma and
 * *                    enables that clock.
 * *****************************************************************/
void Initailize_dma(void);


/******************************************************************
 * * memmove_dma() - This function configures dma for data
 * *                       transfer
 * * uint8_t *src - This is a pointer to the start address of the memory to be moved.
 * * uint8_t *dst - This is a pointer pointer to starting address of the destination memory address.
 * * uint32_t length - Length of the data to be moved
 * ******************************************************************/
void memove_dma(uint8_t *src, uint8_t *dst, uint32_t length);


/******************************************************************
 * * memzero_dma() - This function configures dma for data
 * *                           transfer to set the value to 0
 * * uint8_t *src - This is a pointer to the starting adress of memory which needs to be set to zero.
 * * uint32_t length - Length of memory
 * *******************************************************************/
void memzero_dma(uint8_t *src,uint32_t length);

/******************************************************************
 * * memmove_dma_1_byte() - This function configures dma for byte
 * *                       transfer
 * * uint8_t *src - Pointer to the start of memory to be moved.
 * * uint8_t *dst - Pointer to the destination memory address.
 * * uint32_t length - Length of the data to be moved
 * ******************************************************************/
void memmove_dma_1_byte(uint8_t * src, uint8_t * dst, uint32_t length);


/******************************************************************
 * * memmove_dma_2_byte() - This function configures dma for 16-bit
 * *                           transfer
 * * uint8_t *src - Pointer to the start of memory to be moved.
 * * uint8_t *dst - Pointer to the destination memory address.
 * * uint32_t length - Length of the data to be moved
 * ********************************************************************/
void memmove_dma_2_byte(uint16_t *src,uint16_t * dst, uint32_t length);


/******************************************************************
 * * memmove_dma_4_byte() - This function configures dma for word
 * *                           transfer
 * * uint8_t *src - Pointer to the start of memory to be moved.
 * * uint8_t *dst - Pointer to the destination memory address.
 * * uint32_t length - Length of the data to be moved
 * *******************************************************************/
void memmove_dma_4_byte(uint32_t *src,uint32_t * dst, uint32_t length);


/******************************************************************
 * * memzero_dma_1_byte() - This function configures dma for byte
 * *                           transfer to set the value to 0
 * * uint8_t *src - Pointer to the start of memory
 * * uint32_t length - Length of memory
 * *******************************************************************/
void memzero_dma_1_byte(uint8_t *src,uint32_t length);


/******************************************************************
 * * memzero_dma_2_byte() - This function configures dma for halfword
 * *                           transfer to set the value to 0
 * * uint8_t *src - Pointer to the start of memory
 * * uint32_t length - Length of memory
 * *******************************************************************/
void memzero_dma_2_byte(uint16_t *src,uint32_t length);


/******************************************************************
 * * memzero_dma_4_byte() - This function configures dma for word
 * *                           transfer to set the value to 0
 * * uint8_t *src - Pointer to the start of memory
 * * uint32_t length - Length of memory
 * *******************************************************************/
void memzero_dma_4_byte(uint32_t *src,uint32_t length);

#endif /* DMA_H_ */
