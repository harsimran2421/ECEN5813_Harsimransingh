
#ifndef INCLUDES_CIRCBUF_H_
#define INCLUDES_CIRCBUF_H_
#include <stdint.h>

typedef enum CB_Enum_t{
No_error=1,
Full,
Empty,
Available,
Null_pointer,
No_length,
Buffer_allocation_failure,
Wrong_memory_access,
Error
}CB_status;

typedef struct circular
{
	volatile uint8_t *buffer;
	volatile uint8_t *tail;
	volatile uint8_t *head;
	volatile uint8_t val;
	volatile uint8_t count;
	volatile uint8_t length;
  volatile uint8_t peek;
  CB_status status;
}CB_t;

CB_status CB_buffer_add_item(CB_t *cbuf, uint8_t val);

void memcopy(uint8_t *tail, uint8_t val);

CB_status CB_init(CB_t *cbuf,uint8_t  length);

CB_status CB_buffer_remove_item(CB_t *cbuf/*, uint8_t *value*/);

CB_status CB_is_full(CB_t *cbuf);

CB_status CB_is_empty(CB_t *cbuf);

CB_status CB_peek(CB_t *cbuf, uint8_t position);

CB_status CB_destroy(CB_t *cbuf);


#endif /* INCLUDES_CIRCBUF_H_ */
