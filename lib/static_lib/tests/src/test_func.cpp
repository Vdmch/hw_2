#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "num_of_char.h"
}


// Функция read_number() не принимает неправильные значения номера

TEST(read_number_func, nan_return){
  user test_user = user();

  char tst_number1[] = "bcdefghijk";
  int returned = read_number(&test_user, tst_number1, strlen(tst_number1));
  if (returned != 0) SUCCEED();
  else FAIL();

  char tst_number2[] = "000000000";
  returned = read_number(&test_user, tst_number2, strlen(tst_number2));
  if (returned != 0) SUCCEED();
  else FAIL();
  
  char tst_number3[] = "00000000000";
  returned = read_number(&test_user, tst_number3, strlen(tst_number3));
  if (returned != 0) SUCCEED();
  else FAIL();
}
