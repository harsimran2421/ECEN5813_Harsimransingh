/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 11/27/2017
 * *
 * * File : spi.c
 * * Description : Source file for SPI functions
 * *              -void init_spi()
 * *              -void spi_read_byte(uint8_t * byte)
 * *              -uint8_t spi_write_byte(uint8_t byte)
 * *              -void spi_packet_send(uint8_t * p, size_t length)
 * *              -void flush_spi()
 * ***************************************************************************/
#include "circbuf.h"
#include <stdio.h>
#include "FRDM.h"
#ifdef FRDM
#include <MKL25Z4.h>
#include <stdlib.h>
#include <stdint.h>
#include "spi.h"
#include "gpio.h"
/* Function to initialize SPI0 */
void init_spi()
{
  init_GPIO_nrf();
//Set as Master
  SPI0_C1 = SPI_C1_MSTR_MASK;
//Make Master SS pin to select slave output
  SPI0_C2 = SPI_C2_MODFEN_MASK;
//Set baud rate
  SPI0_BR = (SPI_BR_SPPR(0x02) | SPI_BR_SPR(0x01)); //Set Bitrate to 1Mbps
//Enable SPI0
  SPI0_C1 |= SPI_C1_SPE_MASK;
}

/*Function to read a byte using SPI*/
void spi_read_byte(uint8_t * byte)
{
  while(!(SPI0->S & SPI_S_SPRF_MASK));
  *byte = SPI0->D;
}
 
/*Function to write a byte using SPI*/
  uint8_t spi_write_byte(uint8_t byte)
{
  uint8_t val;
  flush_spi();
  SPI0->D = byte;
  spi_read_byte(&val);
  return val;
}
/*Function to write an array of data using SPI*/
void spi_packet_send(uint8_t * p, size_t length)
{
  size_t i=length;
  while(i)
  {
    spi_write_byte(*(p + length-i));
    i--;
  }
 }
/*Function to block till SPI transmit buffer is empty*/
 void flush_spi()
{
 while(!(SPI0->S & SPI_S_SPTEF_MASK));
}
 #endif
