#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "circbuf.h"
void main()
{
uint8_t retval,retval1;
uint8_t i;
CB_status status = Available;
CB_t *cbuf = malloc(sizeof(CB_t));
CB_init(cbuf, 6); 
for(i=0; i<6; i++)
{
CB_buffer_add_item(cbuf, i);
}
printf("buffer size is:%d\n",cbuf->count);
CB_buffer_remove_item(cbuf);
CB_buffer_remove_item(cbuf);
printf("buffer size is:%d\n",cbuf->count);
//for(i=0; i<3; i++)
//{
//  CB_buffer_add_item(cbuf, i);
//}
//for(i=0; i<=4; i++)
//{
//  CB_buffer_remove_item(cbuf);
//}
status = CB_peek(cbuf, 3);
printf("peek value is %d\n",(cbuf->peek));
if(status == No_error)
  printf("hi\n");
printf("buffer size is: %d\n",cbuf->count);

for (i=0; i<6; i++)
{
  printf("%d\n",*(cbuf->buffer+i));
}
status=CB_destroy(cbuf);
if(status == No_error)
  printf("hi\n");

//printf("%d\n",*(cbuf->buffer+1));
}
