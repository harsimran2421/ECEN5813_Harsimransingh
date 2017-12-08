#include <stdio.h>

int main()
{
  extern uint32_t __BUFFER_START;
  uint8_t * ptr = (uint8_t * )&__BUFFER_START;
}
