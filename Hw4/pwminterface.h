#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define __IO (volatile)
#define __I (volatile const)
typedef struct
{
  volatile uint16_t TCTL;
  volatile uint16_t TCCTL[7];
  volatile uint16_t TCR;
  volatile uint16_t TCCR[7];
  volatile const uint16_t TSTAT;
  uint16_t reserve[6];
  volatile uint16_t TIV[7];
}interface1;
#define PERI_BASE ((uint32_t)0x80000000)
#define interface ((interface1*) PERI_BASE)
