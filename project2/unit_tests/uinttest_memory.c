/******************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 10/27/2017
 * *
 * * File : test_memory.c
 * * Description : Source file for testing memory functions
 * *               -invalid_pointer_test_mymemmove()
 * *               -no_overlap_test_mymemmove()
 * *               -SRC_in_DST_test_mymemmove()
 * *               -DST_in_SRC_test_memmove()
 * *               -invalid_pointer_test_mymemset()
 * *               -valid_test_mymemset()
 * *               -invalid_pointer_test_mymemzero()
 * *               -valid_test_mymemzero()
 * *               -invalid_pointer_test_reverse()
 * *               -odd_length_test_myreverse()
 * *               -even_length_test_myreverse()
 * *               -character256_test_myreverse()
 * *
 * * Testing environment : To test the functions we need
 * * to install the Cmocka framework libraries in our folder
 * * path and make changes to the test Makefile to include
 * * our source files and test files.
 * ********************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "memory.h"
#include <cmocka.h>

/*********************************************************
 * * Defining global variables required for the test function
 * * even_length and odd_length to provide odd and even lengths
 * * test_set[32] array to behave as a memory
 * *********************************************************/
int32_t even_length = 10;
uint32_t odd_length = 11;
uint8_t test_set[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

/****************************************************************
 * * invalid_pointer_test_mymemmove() - This function is used to test NULL pointer
 * * check in mymemmove function.
 * * Input parameter - For this we can send either source or dest as
 * * NULL and some length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer
 * * emum
 * ****************************************************************/

void invalid_pointer_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[0];
    uint8_t *dest = NULL;
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Invalid_pointer);
}

/****************************************************************
 * * no_overlap_test_mymemmove() - This function is used to test my_memmove function
 * * to move data from source to dest memory locations without overlap
 * * Input parameter - For this we send a pointer to valid src and dst
 * * locations along with the length in bytes so they don't overlap
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully move memory and return Pass
 * * enum value.
 * ****************************************************************/
void no_overlap_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[5];
    uint8_t *dest = &test_set[20];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * SRC_in_DST_test_mymemmove() - This function is used to test mymemmove function
 * * to move data from source to dest memory locations with source in dest
 * * overlap
 * * Input parameter - For this we send a pointer to valid source and dest
 * * locations along with the length in bytes so that source is in dest
 * * Assumption - src in dst memory case can be handled by the function
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully move memory with source in
 * * dest and return Pass enum value.
 * ****************************************************************/
void SRC_in_DST_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[15];
    uint8_t *dest = &test_set[10];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * DST_in_SRC_test_mymemmove() - This function is used to test mymemmove function
 * * to move data from src to dst memory locations with dst in src
 * * overlap
 * * Input parameter - For this we send a pointer to valid source and dest
 * * locations along with the length in bytes so that dst is in src
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully move memory with dest in
 * * source and return Pass enum value.
 * ****************************************************************/
void DST_in_SRC_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[10];
    uint8_t *dest = &test_set[15];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * invalid_pointer_test_mymemset() - Function to test NULL pointer
 * * check in mymemset function.
 * * Input parameter - For this we send source as NULL with some value
 * * and length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer
 * * emum
 * ****************************************************************/

void invalid_pointer_test_mymemset(void **state)
{
    uint8_t *source = NULL;
    uint8_t set_value = 10;
    memory_status_t status = my_memset(source, even_length, set_value);
    assert_int_equal(status, Invalid_pointer);
}

/****************************************************************
 * * valid_test_mymemset() - This function is used to test mymemset function to
 * * set a particular value in memory
 * * Input parameter - For this we send a pointer to a valid memory
 * * location along with the length in bytes and value to set
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully set value and return
 * * Pass enum value.
 * ****************************************************************/

void valid_test_mymemset(void **state)
{
    uint8_t *source = &test_set[0];
    uint8_t test_value = 10;
    memory_status_t status = my_memset(source,even_length,test_value);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * invalid_pointer_test_mymemzero() - This function is used to test NULL pointer
 * * check in mymemzero function.
 * * Input parameter - For this we send src as NULL with some length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer
 * * emum vlaue
 * ****************************************************************/
void invalid_pointer_test_mymemzero(void **state)
{
    uint8_t *source = NULL;
    memory_status_t status = my_memzero(source,even_length);
    assert_int_equal(status, Invalid_pointer);
}

/****************************************************************
 * * valid_test_mymemzero() - This function to test mymemzero function to
 * * set zeros in memory
 * * Input parameter - For this we send a pointer to a valid memory
 * * location along with the length in bytes
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully set zeros and return Pass
 * * enum value.
 * ****************************************************************/
void valid_test_mymemzero(void **state)
{
    uint8_t *source = &test_set[0];
    memory_status_t status = my_memzero(source,even_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * invalid_pointer_test_myreverse() - This function is used to test NULL pointer
 * * check in myreverse function.
 * * Input parameter - For this we can send source as NULL and some
 * * length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer
 * * emum value.
 * ****************************************************************/
void invalid_pointer_test_myreverse(void **state)
{
    uint8_t *source = NULL;
    memory_status_t status = my_reverse(source,even_length);
    assert_int_equal(status, Invalid_pointer);
}

/****************************************************************
 * * odd_length_test_myreverse() - This function is used to test myreverse function with
 * * odd length
 * * Input parameter - For this we send a pointer to a valid memory
 * * location along with an odd length in bytes
 * * Assumption: Function is written to handle odd length cases as
 * * well
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully reverse odd memory and
 * * return Pass enum value.
 * ****************************************************************/
void odd_length_test_myreverse(void **state)
{
    uint8_t *source = &test_set[10];
    memory_status_t status = my_reverse(source,odd_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * even_length_test_myreverse() - This functionis used to test myreverse function with
 * * even length
 * * Input parameter - For this we send a pointer to a valid memory
 * * location along with an even length in bytes
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully reverse even memory and
 * * return Pass enum value.
 * ****************************************************************/
void even_length_test_myreverse(void **state)
{
    uint8_t *source = &test_set[10];
    memory_status_t status = my_reverse(source,even_length);
    assert_int_equal(status, Pass);
}

/****************************************************************
 * * character256_test_myreverse() - This function is used to test myreverse function
 * * with all characters
 * * Input parameter - For this we send a pointer to a memory with
 * * all 256 characters
 * * Expected Result - Since it does not have an invalid length or
 * * invalid pointer it should successfully reverse memory and
 * * return Pass enum value.
 * ****************************************************************/
void character256_test_myreverse(void **state)
{
  uint8_t test_set[256];
  uint8_t test_check[256];
  uint16_t i;
  for(i=0;i<256;i++)
  {
  test_set[i] = i;
  test_check[i] = i;
  }
  uint8_t *source = test_set;
  memory_status_t status = my_reverse(source,256);
  for(i=0;i<256;i++)
  {
  if(test_set[i]!=test_check[255-i])
  {
    status = Fail;
    break;
  }
  }
  if(i == 256)
    assert_int_equal(status, Pass);
  else assert_int_equal(status, Fail);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(invalid_pointer_test_mymemmove),
  cmocka_unit_test(no_overlap_test_mymemmove),
  cmocka_unit_test(SRC_in_DST_test_mymemmove),
  cmocka_unit_test(DST_in_SRC_test_mymemmove),
  cmocka_unit_test(invalid_pointer_test_mymemset),
  cmocka_unit_test(valid_test_mymemset),
  cmocka_unit_test(invalid_pointer_test_mymemzero),
  cmocka_unit_test(valid_test_mymemzero),
  cmocka_unit_test(invalid_pointer_test_myreverse),
  cmocka_unit_test(odd_length_test_myreverse),
  cmocka_unit_test(even_length_test_myreverse),
  cmocka_unit_test(character256_test_myreverse),
};
  return cmocka_run_group_tests(tests, NULL, NULL);
}
