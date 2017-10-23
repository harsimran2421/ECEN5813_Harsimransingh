#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include "memory.h"
#include <cmocka.h>

int32_t even_length = 10;
uint32_t odd_length = 11;
uint8_t test_set[32] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};

void invalid_pointer_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[0];
    uint8_t *dest = NULL;
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Invalid_pointer);
}

void no_overlap_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[5];
    uint8_t *dest = &test_set[20];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

void SRC_in_DST_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[15];
    uint8_t *dest = &test_set[10];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

void DST_in_SRC_test_mymemmove(void **state)
{
    uint8_t *source = &test_set[10];
    uint8_t *dest = &test_set[15];
    memory_status_t status = my_memmove(source,dest,even_length);
    assert_int_equal(status, Pass);
}

void invalid_pointer_test_mymemset(void **state)
{
    uint8_t *source = NULL;
    uint8_t set_value = 10;
    memory_status_t status = my_memset(source, even_length, set_value);
    assert_int_equal(status, Invalid_pointer);
}

void valid_test_mymemset(void **state)
{
    uint8_t *source = &test_set[0];
    uint8_t test_value = 10;
    memory_status_t status = my_memset(source,even_length,test_value);
    assert_int_equal(status, Pass);
}

void invalid_pointer_test_mymemzero(void **state)
{
    uint8_t *source = NULL;
    memory_status_t status = my_memzero(source,even_length);
    assert_int_equal(status, Invalid_pointer);
}

void valid_test_mymemzero(void **state)
{
    uint8_t *source = &test_set[0];
    memory_status_t status = my_memzero(source,even_length);
    assert_int_equal(status, Pass);
}

void invalid_pointer_test_myreverse(void **state)
{
    uint8_t *source = NULL;
    memory_status_t status = my_reverse(source,even_length);
    assert_int_equal(status, Invalid_pointer);
}

void odd_length_test_myreverse(void **state)
{
    uint8_t *source = &test_set[10];
    memory_status_t status = my_reverse(source,odd_length);
    assert_int_equal(status, Pass);
}

void even_length_test_myreverse(void **state)
{
    uint8_t *source = &test_set[10];
    memory_status_t status = my_reverse(source,even_length);
    assert_int_equal(status, Pass);
}

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
