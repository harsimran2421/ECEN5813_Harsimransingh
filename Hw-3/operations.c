#include <stdio.h>
#include <math.h>

void main()
{
	unsigned char arr[8];
	int i = 0;
	arr [0] = 0xEE;
	arr [1] = 0x12;
	arr [2] = 0x77;
	arr [3] = 0xBE;
	arr [4] = 0x66;
	arr [5] = 0x54;
	arr [6] = 0x33;
	arr [7] = 0xF0;
	unsigned char *ptr = arr;
	*ptr = 0xF1&127;
	ptr++;
	*ptr+=17;
	ptr+=2;
	*ptr=15%4;
	ptr--;
	*ptr>>=4;
	ptr=&arr[5];
	*ptr=(1<<5)|(4<<2);
	ptr = &arr[7];
	*ptr = 22; 
	ptr = arr;
	printf("Address     Data\n");
	for(i = 0; i<=7 ; i++)
	{
		printf("%d         0X%X\n", (100+i), *ptr++);
	}
}
