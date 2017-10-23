#include <stdio.h>
#include <stdint.h>
#define SET_EQUAL(a,b) (a=(uint8_t)b)
//#define SQUARE(a) (a*a)
//#define BASE 16
//#define OFFSET (10+BASE)
//int8_t var = OFFSET*2;
void main(){
uint8_t a=7;
uint8_t b=-8;
SET_EQUAL(a,b);
//b=SQUARE(a++);
printf("%d\n",a);
}
