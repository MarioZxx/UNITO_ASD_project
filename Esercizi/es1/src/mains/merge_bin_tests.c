#include <stdio.h>
#include <stdlib.h>
#include "../unity/unity.h"
#include "../mergebinary/merge_binary.h"

//unity tests
//precedence relation used in tests
static int precedes_int(void *i1_p, void *i2_p) {
  int *int1_p = (int*)i1_p;
  int *int2_p = (int*)i2_p;
  return *int1_p < *int2_p;
}

static void test_sorting_array_is_empty_zero_el() {
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  TEST_ASSERT_TRUE(sorting_array_is_empty(sorting_array_int));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_is_empty_one_el() {
  int i = -12;
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  sorting_array_add(sorting_array_int, &i, 0);
  TEST_ASSERT_FALSE(sorting_array_is_empty(sorting_array_int));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_size_zero_el() {
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  TEST_ASSERT_EQUAL_INT(0, sorting_array_size(sorting_array_int));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_size_one_el() {
  int i1 = -12;
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  sorting_array_add(sorting_array_int, &i1, 0);
  TEST_ASSERT_EQUAL_INT(1, sorting_array_size(sorting_array_int));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_size_two_el() {
  int i1 = -12;
  int i2 = 2;
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  sorting_array_add(sorting_array_int, &i2, 0);
  sorting_array_add(sorting_array_int, &i1, 1);
  m_bi_sort(sorting_array_int,0,1);
  TEST_ASSERT_EQUAL_INT(2, sorting_array_size(sorting_array_int));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_add_get_one_el() {
  int i1 = -12;
  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  sorting_array_add(sorting_array_int, &i1, 0);
  TEST_ASSERT_EQUAL_PTR(&i1, sorting_array_get(sorting_array_int, 0));
  sorting_array_free_memory(sorting_array_int);
}

static void test_sorting_array_add_get_three_el() {
  int i1 = -12;
  int i2 = 0;
  int i3 = 4;
  int* exp_arr[] = {&i1, &i2, &i3};

  SortingArray *sorting_array_int = sorting_array_create(precedes_int);
  sorting_array_add(sorting_array_int, &i2, 0);
  sorting_array_add(sorting_array_int, &i3, 1);
  sorting_array_add(sorting_array_int, &i1, 2);
  m_bi_sort(sorting_array_int,0,1);

  int **act_arr = malloc(3*sizeof(int*));
  for (int i=0; i < 3; ++i) {
    act_arr[i] = (int*)sorting_array_get(sorting_array_int, i);
  }
  TEST_ASSERT_EQUAL_PTR_ARRAY(exp_arr, act_arr, 3);
  free(act_arr);
  sorting_array_free_memory(sorting_array_int);
}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_sorting_array_is_empty_one_el);
  RUN_TEST(test_sorting_array_size_two_el);
  RUN_TEST(test_sorting_array_add_get_three_el);
  RUN_TEST(test_sorting_array_size_one_el);
  RUN_TEST(test_sorting_array_is_empty_zero_el);
  RUN_TEST(test_sorting_array_size_zero_el);
  RUN_TEST(test_sorting_array_add_get_one_el);
  return UNITY_END();
}
