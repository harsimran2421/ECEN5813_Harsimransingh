#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

uint8_t buff_length = 6;
uint8_t test_data[6] = {1,2,3,4,5,6};

void test_circbuf_allocate_free(void **state)
{
  CB_t *test_buff = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buff, buff_length);
  CB_status status = CB_destroy(test_buff);
  assert_int_equal(status, No_error);
}

void test_circbuf_invalid_pointer(void **state)
{
    CB_status status = CB_is_full(NULL);
    assert_int_equal(status,Null_pointer);
}

void non_initialized_circbuf_test(void **state)
{
 CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
 CB_init(test_buffer, buff_length);
 CB_status status;
 if(((test_buffer->head) == (test_buffer->buffer)) && ((test_buffer->tail) == (test_buffer->buffer)))
  {
    status = No_error;
  }
  else status = Null_pointer;
  assert_int_equal(status, No_error);
}

void test_circbuf_add_remove(void **state)
{ uint8_t i=0;
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status;
  for(i=0; i<=5; i++)
  {
    CB_buffer_add_item(test_buffer,i);
  }
  for(i=0; i<=5; i++)
  {
    status = CB_buffer_remove_item(test_buffer);
  }
  assert_int_equal(status, No_error);
}

void test_circbuf_buffer_full(void **state)
{
  uint8_t i=0;
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  for(i=0; i<11; i++)
  {
    CB_buffer_add_item(test_buffer,i);
  }
  CB_status status = CB_is_full(test_buffer);
  assert_int_equal(status, Full);
}

void test_circbuf_buffer_empty(void **state)
{
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status = CB_is_empty(test_buffer);
  assert_int_equal(status, Empty);
}

void test_circbuf_wrap_add(void **state)
{
  uint8_t i =0;
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  uint8_t *last = (uint8_t *)(test_buffer->head);
  for(i=0;i<buff_length; i++)
  {
    CB_buffer_add_item(test_buffer,i);
  }
  CB_status status;
  if((test_buffer->head)==last)
    status = No_error;
  else status = Error;

  assert_int_equal(status, No_error);
}

void test_circbuf_wrap_remove(void **state)
{
  uint8_t i=0;
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  uint8_t *last = (uint8_t *)(test_buffer->tail);
  for(i=0; i<buff_length; i++)
  {
    CB_buffer_add_item(test_buffer,i);
  }
  for(i=0;i<buff_length;i++)
  {
    CB_buffer_remove_item(test_buffer);
  }
  CB_status status;
  if((test_buffer->tail)==last)
    status = No_error;
  else status = Error;

  assert_int_equal(status, No_error);
}

void test_circbuf_over_fill(void **state)
{
  uint8_t i=0;
  CB_t *test_buffer = (CB_t *) malloc(sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status;
  for(i=0; i<=buff_length; i++)
  {
    status = CB_buffer_add_item(test_buffer,i);
  }
  assert_int_equal(status, Full);
}

void test_circbuf_over_empty(void **state)
{
  CB_t *test_buffer = (CB_t *) malloc(sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status = CB_buffer_remove_item(test_buffer);
  assert_int_equal(status, Empty);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(test_circbuf_allocate_free),
  cmocka_unit_test(test_circbuf_invalid_pointer),
  cmocka_unit_test(non_initialized_circbuf_test),
  cmocka_unit_test(test_circbuf_add_remove),
  cmocka_unit_test(test_circbuf_buffer_full),
  cmocka_unit_test(test_circbuf_buffer_empty),
  cmocka_unit_test(test_circbuf_wrap_add),
  cmocka_unit_test(test_circbuf_wrap_remove),
  cmocka_unit_test(test_circbuf_over_fill),
  cmocka_unit_test(test_circbuf_over_empty),
};
  return cmocka_run_group_tests(tests, NULL, NULL);
}
