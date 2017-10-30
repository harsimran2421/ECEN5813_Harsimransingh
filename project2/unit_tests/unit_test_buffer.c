/******************************************************
 * * Authors : Harsimransingh Bindra
 * * * Date : 10/27/2017
 * *
 * * File : test_memory.c
 * * Description : Source file for testing memory functions
 * *               -testcircbuf_allocate_free()
 * *               -testcircbuf_invalid_pointer()
 * *               -testcircbuf_non_initialized_buffer()
 * *               -testcircbuf_add_remove()
 * *               -testcircbuf_buffer_full()
 * *               -testcircbuf_buffer_empty()
 * *               -testcircbuf_wrap_add()
 * *               -testcircbuf_wrap_remove()
 * *               -testcircbuf_over_fill()
 * *               -testcircbuf_over_empty()
 * *
 * * Testing environment : To test the functions we need
 * * to install the Cmocka framework libraries in our folder
 * * path and make changes to the test Makefile to include
 * * our source files and test files.
 * ********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "circbuf.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

/*********************************************************
 * * Defining the Global variables required for out test function
 * * buff_length gives length of buffer to access
 * * test_data[6] array to behave as a buffer
 * *********************************************************/
uint8_t buff_length = 6;
uint8_t test_data[6] = {1,2,3,4,5,6};

/***********************************************************************
 * * testcircbuf_allocate_free() - This function is used to test CB_init
 * * function and CB_Destroy function to check if buffer function can be used
 * * to allocate and free memory from heap
 * * Input parameter - For this we send the test_buff structure pointer.
 * * to CB_init function and pass it again to the destory function
 * * Expected Result - Receive a No_error enum from the functions
 * ***********************************************************************/
void testcircbuf_allocate_free(void **state)
{
  CB_t *test_buff = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buff, buff_length);
  CB_status status = CB_destroy(test_buff);
  assert_int_equal(status, No_error);
}

/***********************************************************************
 * * testcircbuf_invalid_pointer() -This  function is used to test if circular buffer function
 * * can handle invalid pointer(NULL)
 * * Input parameter - Here we send a NULL pointer to the
 * * CB_is_full function
 * * Expected Result - Receive a Null_pointer enum from the function
 * ***********************************************************************/
void testcircbuf_invalid_pointer(void **state)
{
    CB_status status = CB_is_full(NULL);
    assert_int_equal(status,Null_pointer);
}

/***********************************************************************
 * * noninitialized_circbuf_test() - This function is used to test if circular
 * * buffer is initialized before using.
 * * Input parameter - For this we allocate memory to the circular buffer
 * * and send it to initialize function
 * * Expected Result - Check if head and tail points towards the buffer and set
 * * No_error enum
 * ***********************************************************************/

void noninitialized_circbuf_test(void **state)
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

/*********************************************************************
 * * testcircbuf_add_remove() - This function is used to test if circular buffer can
 * * add and remove data to the buffer
 * * Input parameter - For this we initialize our circular buffer and add data to the buffer
 * * and then remove the data and check for the returned enum value
 * * Expected Result - Receive a No_error enum from the functions
 * *********************************************************************/
void testcircbuf_add_remove(void **state)
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

/***********************************************************************
 * * testcircbuf_buffer_full() - This function is used to test if circular buffer is
 * * full and return corresponding enum value
 * * Input parameter - For this we initialize the circular buffer and add data to it
 * * until the circular buffer is full
 * * Expected Result - Receive a Full enum from the function
 * ***********************************************************************/
void testcircbuf_buffer_full(void **state)
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

/***********************************************************************
 * * testcircbuf_buffer_empty() - This functionis used  to test if circular buffer is
 * * empty and return corresponding enum value
 * * Input parameter - For this we initialize the circular buffer and add no data to it
 * * but directly call our remove function
 * * Expected Result - Since buffer is already empty we should receive a
 * * Empty enum from the function
 * ***********************************************************************/
void testcircbuf_buffer_empty(void **state)
{
  CB_t *test_buffer = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status = CB_is_empty(test_buffer);
  assert_int_equal(status, Empty);
}

/***********************************************************************
 * * testcircbuf_wrap_add() - This Function is used to test if the circular buffer can wrap
 * * near the boundary when data is added to the circular buffer.
 * * Input parameter - For this we initialize buffer and add data to it
 * * until buffer is full and check the head pointer with its previous value
 * * Expected Result - If the head pointer and previous value point
 * * at the same position then there is no error and No_error enum value should be set.
 * ***********************************************************************/

void testcircbuf_wrap_add(void **state)
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

/***********************************************************************
 * * testcircbuf_wrap_remove() - This function is used to test if circular buffer can
 * * wrap near the boundary when data is removed from it.
 * * Input parameter - For this we initialize buffer and add data to it
 * * until buffer is full and remove the same amount of data then check the
 * * tail pointer with its previous value.
 * * Expected Result - If the tail pointer and previous value point
 * * at the same position then there is no error and No_error enum value should be set
 * ***********************************************************************/
void testcircbuf_wrap_remove(void **state)
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

/***********************************************************************
 * * testcircbuf_over_fill() - This function is used to test if the circular buffer can
 * * handle when more data is added than its size
 * * Input parameter - For this we initialize buffer and add data more
 * * than its capacity
 * * Expected Result - Once the buffer is full if anymore data is addded to
 * * it, it will return a Full enum from the function
 * ***********************************************************************/

void testcircbuf_over_fill(void **state)
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

/***********************************************************************
 * * testcircbuf_over_empty() - This function is used to test if circular buffer can
 * * handle when more data is removed than available in the buffer
 * * Input parameter - For this we initialize buffer and call our remove function
 * * Expected Result - Since the buffer is already empty if we rempve anymore
 * * data from it it will return a Empty enum from the function
 * ***********************************************************************/
void testcircbuf_over_empty(void **state)
{
  CB_t *test_buffer = (CB_t *) malloc(sizeof(CB_t));
  CB_init(test_buffer, buff_length);
  CB_status status = CB_buffer_remove_item(test_buffer);
  assert_int_equal(status, Empty);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(testcircbuf_allocate_free),
  cmocka_unit_test(testcircbuf_invalid_pointer),
  cmocka_unit_test(noninitialized_circbuf_test),
  cmocka_unit_test(testcircbuf_add_remove),
  cmocka_unit_test(testcircbuf_buffer_full),
  cmocka_unit_test(testcircbuf_buffer_empty),
  cmocka_unit_test(testcircbuf_wrap_add),
  cmocka_unit_test(testcircbuf_wrap_remove),
  cmocka_unit_test(testcircbuf_over_fill),
  cmocka_unit_test(testcircbuf_over_empty),
};
  return cmocka_run_group_tests(tests, NULL, NULL);
}
