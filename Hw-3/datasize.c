#include <stdio.h>
#include <stdint.h>

void print_arch_data()
{
	printf("Size of char data type is : %lo Byte\n", sizeof(char));
        printf("Size of int data type is : %lo Byte\n", sizeof(int));
	printf("Size of float data type is : %lo Byte\n", sizeof(float));
	printf("Size of double data type is : %lo Byte\n", sizeof(double));
	printf("Size of short data type is : %lo Byte\n", sizeof(short));
	printf("Size of long data type is : %lo Byte\n", sizeof(long));
	printf("Size of long int data type is : %lo Byte\n", sizeof(long int));
	printf("Size of long long data type is : %lo Byte\n", sizeof(long long));
	printf("Size of int8_t data type is : %lo Byte\n", sizeof(int8_t));
	printf("Size of uint8_t data type is : %lo Byte\n", sizeof(uint8_t));
	printf("Size of uint16_t data type is : %lo Byte\n", sizeof(uint16_t));
	printf("Size of uint32_t data type is : %lo Byte\n", sizeof(uint32_t));
	printf("Size of char* data type is : %lo Byte\n", sizeof(char*));
	printf("Size of int* data type is : %lo Byte\n", sizeof(int*));
	printf("Size of float* data type is : %lo Byte\n", sizeof(float*));
	printf("Size of void* data type is : %lo Byte\n", sizeof(void*));
	printf("Size of void** data type is : %lo Byte\n", sizeof(void**));
	printf("Size of int8_t* data type is : %lo Byte\n", sizeof(int8_t*));
	printf("Size of int16_t* data type is : %lo Byte\n", sizeof(int16_t*));
	printf("Size of int32_t* data type is : %lo Byte\n", sizeof(int32_t*));
	printf("Size of size_t data type is : %lo Byte\n", sizeof(size_t));
}
void main()
{
	print_arch_data();
}
