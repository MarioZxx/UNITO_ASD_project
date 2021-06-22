#include "unity/unity.h"
#include "edit_distance.h"

//unity tests
static void test_edit_distance_with_empty_strings() {
  char *str1="";
  char *str2="";
  TEST_ASSERT_TRUE(edit_distance(str1,str2) == 0);
}

static void test_edit_distance_with_upper_case() {
  char *str1="a";
  char *str2="A";
  TEST_ASSERT_EQUAL_INT(0, edit_distance(str1,str2));
}

static void test_edit_distance_with_short_string() {
  char *str1="ciao";
  char *str2="bao";
  TEST_ASSERT_EQUAL_INT(3, edit_distance(str1,str2));
}

static void test_edit_distance_with_long_string() {
  char *str1="universita";
  char *str2="informatica";
  TEST_ASSERT_EQUAL_INT(13, edit_distance(str1,str2));
}

static void test_edit_distance_dyn_with_empty_strings() {
  char *str1="";
  char *str2="";
  TEST_ASSERT_TRUE(edit_distance_dyn_ric(str1,str2) == 0);
}

static void test_edit_distance_dyn_with_upper_case() {
  char *str1="a";
  char *str2="A";
  TEST_ASSERT_EQUAL_INT(0, edit_distance_dyn_ric(str1,str2));
}

static void test_edit_distance_dyn_with_short_string() {
  char *str1="ciao";
  char *str2="bao";
  TEST_ASSERT_EQUAL_INT(3, edit_distance_dyn_ric(str1,str2));
}

static void test_edit_distance_dyn_with_long_string() {
  char *str1="universita";
  char *str2="informatica";
  TEST_ASSERT_EQUAL_INT(13, edit_distance_dyn_ric(str1,str2));
}


int main() {
  UNITY_BEGIN();
  RUN_TEST(test_edit_distance_dyn_with_long_string);
  RUN_TEST(test_edit_distance_with_empty_strings);
  RUN_TEST(test_edit_distance_dyn_with_short_string);
  RUN_TEST(test_edit_distance_dyn_with_empty_strings);
  RUN_TEST(test_edit_distance_with_upper_case);
  RUN_TEST(test_edit_distance_dyn_with_upper_case);
  RUN_TEST(test_edit_distance_with_short_string);
  RUN_TEST(test_edit_distance_with_long_string);
  return UNITY_END();
}
