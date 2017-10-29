#include<stdio.h>
#include<stdint.h>
#include"conversion.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void invalid_test_big_to_little(void **state)
{
  uint32_t *source = NULL;
  uint32_t test_length = 4;
  conversion_status_t status = big_to_little32((uint32_t *)source,test_length);
  assert_int_equal(status, Invalid_pointer);
}

void invalid_test_little_to_big(void **state)
{
  uint32_t *source = NULL;
  uint32_t test_length = 4;
  conversion_status_t status = little_to_big32((uint32_t *)source,test_length);
  assert_int_equal(status, Invalid_pointer);
}

void valid_conversion_test_big_to_little(void **state)
{
  uint32_t test_data = 0x12345678;
  uint32_t *ptr = &test_data;
  uint32_t length = 4;
  conversion_status_t status = big_to_little32(ptr,length);
  assert_int_equal(status, Pass);
}

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
