#include <stdio.h>
#include "reverse.h"

void main()
{
	char string[] = "Harsimansingh";			/*input string*/
	char test;						/*to store the return value of the reverse function*/
	int i=0;
	int length=0;
	printf("Input string is : ");
	while(string[i] != '\0')				/*loop to calculate the length of the string*/
	{       printf("%c",string[i]);
		length++;
		i++;
	}
	printf("\nLength of the string is : %d\n", length);
	test = reverse(&string[0], length);
	if(test == 'F')						/*condition to handle errors*/
	{
		printf("\nRecieved character is %c\n",test);
		printf("String reverse failed\n");
	}
	else
	{	printf("Reversed string is : ");
		for(i=0; i<=(length-1); i++)
		{
			printf("%c",string[i]);
		}
		printf("\nRecieved character is:%c\n",test);

	}
}
