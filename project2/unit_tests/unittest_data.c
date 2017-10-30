/******************************************************
 * * Authors : Smitesh Modak, Harsimransingh
 * * Date : 02/28/2017
 * *
 * * File : unitest_data.c
 * * Description : Source file for testing data functions
 * *               -invalid_test_big_to_little()
 * *               -invalid_test_little_to_big()
 * *               -valid_conversion_test_big_to_little()
 * *               -valid_conversion_test_little_to_big()
 * * Testing environment : To test the functions we need
 * * to install the Cmocka framework libraries in our folder
 * * path and make changes to the test Makefile to include
 * * our source files and test files.
 * ******************************************************/
#include<stdio.h>
#include<stdint.h>
#include"conversion.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
/************************************************************
 * * invvalid_test_big_to_little() - Function to test NULL pointer
 * * check in bit_to_little32 function.
 * * Input parameter - For this we send the NULL pointer as an input
 * * parameter along with some length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer emum value
 * *************************************************************/
void invalid_test_big_to_little(void **state)
{
  uint32_t *source = NULL;
  uint32_t test_length = 4;
  conversion_status_t status = big_to_little32((uint32_t *)source,test_length);
  assert_int_equal(status, Invalid_pointer);
}

/************************************************************
 * * invalid_test_little_to_big() - This function is used to test NULL pointer
 * * check in little_to_big32 function.
 * * Input parameter - For this we send the NULL pointer as an input
 * * parameter along with some length
 * * Expected Result - Since an invalid(NULL) pointer is passed as a
 * * parameter the function should return an Invalid_pointer emum value
 * *
 * *************************************************************/
void invalid_test_little_to_big(void **state)
{
  uint32_t *source = NULL;
  uint32_t test_length = 4;
  conversion_status_t status = little_to_big32((uint32_t *)source,test_length);
  assert_int_equal(status, Invalid_pointer);
}

/************************************************************
 * * valid_conversion_test_big_to_little() -This function is used to test a
 * * valid conversion using big_to_little32 function.
 * * Input parameter - For this we send a pointer to a valid data
 * * along with the length in bytes
 * * Expected Result - Since it does not have an invalid pointer or
 * * invalid length it should successfully convert data and return Pass
 * * enum value.
 * *************************************************************/
void valid_conversion_test_big_to_little(void **state)
{
  uint32_t test_data = 0x12345678;
  uint32_t *ptr = &test_data;
  uint32_t length = 4;
  conversion_status_t status = big_to_little32(ptr,length);
  assert_int_equal(status, Pass);
}

/************************************************************
 * * valid_conversion_test_little_to_big() - This function to test a
 * * valid conversion using little_to_big32 function.
 * * Input parameter - For this we send a pointer to a valid data
 * * along with the length in bytes
 * * Expected Result - Since it does not have an invalid pointer or
 * * invalid length it should successfully convert data and return Pass
 * * enum value.
 * *************************************************************/
void valid_conversion_test_little_to_big(void **state)
{
  uint32_t test_data = 0x12345678;
  uint32_t *source = &test_data;
  uint32_t length = 4;
  conversion_status_t status = little_to_big32(source,length);
  assert_int_equal(status, Pass);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
  cmocka_unit_test(invalid_test_big_to_little),
  cmocka_unit_test(invalid_test_little_to_big),
  cmocka_unit_test(valid_conversion_test_big_to_little),
  cmocka_unit_test(valid_conversion_test_little_to_big),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
