#include <stdio.h>
/*reverse function reverses the string where the str pointer points to*/
char reverse(char *str, int length)
{
	int i;
	char *temp;				/*temporary pointer variable used to point to the end of the string*/
	char swap;                     		/*temporary char variable used for swapping*/
	temp = str + (length-1)*sizeof(char);   /*pointing the temp pointer to the end of the string*/
	if(length<=0)				/*handling error for wrong input*/
	{
		return 'F';			
	}
	if(length%2 != 0)			/*to check where length of string is even or odd and make strings with odd length even*/
	{
		length = length-1;

	}
	for(i=0; i<(length/2); i++)		/*loop statement used to reverse the string*/	{
		swap = *temp;
		*temp = *str;
		*str = swap;
		str++;
		temp--;
	}
	return '0';
}
