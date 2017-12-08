#include <stdint.h>
#include "circbuf.h"
#include "memory.h"
#include "FRDM.h"


/*Compile time switch for FRDM*/
#ifdef FRDM
#include "DMA.h"
#include "MKL25Z4.h"

#define DMA_ENABLE_TRANSFER (0x80)
#define DMA_START_BIT_ENABLE (0x10000)
#define DISABLE_DMA (0x00)
#define DMA_CHANNEL0 (0x3C)
#define ENABLE_DMAMUX_CLOCK (0x00000002)
#define ENABLE_DMA_CLOCK (0x00000100)
#define DMA_DCR0_UART (0xE09A0000)
#define DMA_DCR0_8BIT_MEMMOVE (0x805A0000)
#define DMA_DCR0_8BIT_MEMZERO (0x801A0000)
#define DMA_DCR0_16BIT_MEMMOVE (0x806C0000)
#define DMA_DCR0_16BIT_MEMZERO (0x802C0000)
#define DMA_DCR0_32BIT_MEMMOVE (0x80480000)
#define DMA_DCR0_32BIT_MEMZERO (0x80080000)
#define DMA_CLOCK_DISABLE (0x7FFFFFFF)
/*Function to select and enable clock for DMA*/
void Initailize_dma(void)
{
/*enable clock for DMA mux clock gate control*/
  SIM_SCGC6=ENABLE_DMAMUX_CLOCK;

/*enable clock for DMA clock gate control*/
  SIM_SCGC7=ENABLE_DMA_CLOCK;

/*disable dma before configuration*/
  DMAMUX0_CHCFG0=DISABLE_DMA;

  DMA_DCR0|=DMA_DCR_EINT_MASK;
}


void memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length)
{
uint32_t word=0;
uint32_t remainder=0;
uint32_t half_word=0;
if(length!=0)
{
  word=length/4;
  remainder=length%4;
  half_word=remainder/2;
  remainder=remainder%2;
  if(word!=0)
    {
      memmove_dma_4_byte(src,dst,word);
    }
  if(half_word!=0)
  {
    src=src+(word*4);
    dst=dst+(word*4);
    memmove_dma_2_byte(src,dst,half_word);
  }
  if(remainder!=0)
  {
    src=src+(half_word*2);
    dst=dst+(half_word*2);
    memmove_dma_1_byte(src,dst,remainder);
  }
  }
}

void memzero_dma(uint8_t *src, uint32_t length)
{
uint32_t word=0;
uint32_t remainder=0;
uint32_t half_word=0;
if(length!=0)
{
  word=length/4;
  remainder=length%4;
  half_word=remainder/2;
  remainder=remainder%2;
  if(word!=0)
    {
      memzero_dma_4_byte(src,word);
    }
  if(half_word!=0)
  {
    src=src+(word*4);
    memzero_dma_2_byte(src,half_word);
  }
  if(remainder!=0)
  {
    src=src+(half_word*2);
    memzero_dma_1_byte(src,remainder);
  }
  }
}


void memmove_dma_1_byte(uint8_t * src, uint8_t * dst, uint32_t length)
{
  /*overlapping condition*/
  if((src<dst) && (dst-length)<src)
  {
    uint8_t tmp[length];
/* Disable DMAtransfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_8BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)&tmp;
/*load the length value*/
    DMA_DSR_BCR0=length;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_8BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)&tmp;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
  else
  {
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_8BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
}

void memmove_dma_2_byte(uint8_t * src, uint8_t * dst, uint32_t length)
{
  /*overlapping condition*/
  if((src<dst) && (dst-length)<src)
  {
    uint8_t tmp[length];
/* Disable DMAtransfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_16BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)&tmp;
/*load the length value*/
    DMA_DSR_BCR0=length*4;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_16BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)&tmp;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
  else
  {
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_16BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length*4;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
}

void memmove_dma_4_byte(uint8_t *src, uint8_t *dst, uint32_t length)
{
  /*overlapping condition*/
  if((src<dst) && (dst-length)<src)
  {
    uint8_t tmp[length];
/* Disable DMAtransfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_32BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)&tmp;
/*load the length value*/
    DMA_DSR_BCR0=length*4;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_32BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)&tmp;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
  else
  {
/*Disable DMA transfer until configuration is completed*/
    DMA_DCR0=DMA_DCR0_32BIT_MEMMOVE;
/*assign source address*/
    DMA_SAR0=(uint32_t)src;
/*assign destination address*/
    DMA_DAR0=(uint32_t)dst;
/*load the length value*/
    DMA_DSR_BCR0=length*4;
/*select channel source slot*/
    DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
    DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
    DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
    NVIC_EnableIRQ(DMA0_IRQn);
  }
}

void memzero_dma_1_byte(uint8_t *src,uint32_t length)
{
  uint16_t set=0;
/*Disable DMA transfer until configuration is completed*/
  DMA_DCR0=DMA_DCR0_8BIT_MEMZERO;
/*assign source address*/
  DMA_SAR0=(uint32_t)&set;
/*assign destination address*/
  DMA_DAR0=(uint32_t)src;
/*load the length value*/
  DMA_DSR_BCR0=length;
/*select channel source slot*/
  DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
  DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
  DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
  NVIC_EnableIRQ(DMA0_IRQn);
}

void memzero_dma_2_byte(uint8_t *src,uint32_t length)
{
  uint16_t set=0;
/*Disable DMA transfer until configuration is completed*/
  DMA_DCR0=DMA_DCR0_16BIT_MEMZERO;
/*assign source address*/
  DMA_SAR0=(uint32_t)&set;
/*assign destination address*/
  DMA_DAR0=(uint32_t)src;
/*load the length value*/
  DMA_DSR_BCR0=length;
/*select channel source slot*/
  DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
  DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
  DMA_DCR0|=DMA_START_BIT_ENABLE;
/*Indicate DMA transfer is complete*/
  NVIC_EnableIRQ(DMA0_IRQn);
}

void memzero_dma_4_byte(uint8_t *src,uint32_t length)
{
  uint16_t set=0;
/*Disable DMA transfer until configuration is completed*/
  DMA_DCR0=DMA_DCR0_32BIT_MEMZERO;
/*assign source address*/
  DMA_SAR0=(uint32_t)&set;
/*assign destination address*/
  DMA_DAR0=(uint32_t)src;
/*load the length value*/
  DMA_DSR_BCR0=length;
/*select channel source slot*/
  DMAMUX0_CHCFG0|=DMA_CHANNEL0;
/*enable DMA transfer*/
  DMAMUX0_CHCFG0|=DMA_ENABLE_TRANSFER;
/*enable start bit*/
  DMA_DCR0|=DMA_START_BIT_ENABLE;

/*Indicate DMA transfer is complete*/
  NVIC_EnableIRQ(DMA0_IRQn);
}

void DMA0_IRQHandler()
{
	__disable_irq();
	DMA_DCR0 &=DMA_CLOCK_DISABLE;
	DMA_DSR_BCR0=DMA_DSR_BCR_DONE_MASK;
	__enable_irq();
}
#endif
