#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "test_lib_funcs.h"
}


// Функция read_number() не принимает неправильные значения номера

TEST(add_to_series, nan_return){
  int returned = add_to_series(NULL, 'a');
  EXPECT_EQ(returned, -1);
}

#define TEST_CHAR_SERIES(series, symbols_0, symbols_1, symbols_2, symbols_3, symbols_4, symbols_5, symbols_6, symbols_7, count_num, len_num) \
            EXPECT_EQ(returned, 0); \
            EXPECT_EQ(series->symbols[0], symbols_0); \
            EXPECT_EQ(series->symbols[1], symbols_1); \
            EXPECT_EQ(series->symbols[2], symbols_2); \
            EXPECT_EQ(series->symbols[3], symbols_3); \
            EXPECT_EQ(series->symbols[4], symbols_4); \
            EXPECT_EQ(series->symbols[5], symbols_5); \
            EXPECT_EQ(series->symbols[6], symbols_6); \
            EXPECT_EQ(series->symbols[7], symbols_7); \
            EXPECT_EQ(series->count, count_num); \
            EXPECT_EQ(series->len, len_num)

TEST(add_to_series, correct_adding){
  char_series* series = new char_series;
  series->symbols[0] = 0; 
  series->symbols[1] = 0; 
  series->symbols[2] = 0; 
  series->symbols[3] = 0; 
  series->symbols[4] = 0; 
  series->symbols[5] = 0; 
  series->symbols[6] = 0; 
  series->symbols[7] = 0; 
  series->count = 0; 
  series->len = 0; 

  // symbols[0]
  int returned = add_to_series(series, 1);
  TEST_CHAR_SERIES(series,2,0,0,0,0,0,0,0,1,0);
  returned = add_to_series(series, 1);
  TEST_CHAR_SERIES(series,2,0,0,0,0,0,0,0,2,0);
  
  // symbols[1]
  returned = add_to_series(series, 33);
  TEST_CHAR_SERIES(series,2,2,0,0,0,0,0,0,3,0);
  returned = add_to_series(series, 33);
  TEST_CHAR_SERIES(series,2,2,0,0,0,0,0,0,4,0);

  // symbols[2]
  returned = add_to_series(series, 65);
  TEST_CHAR_SERIES(series,2,2,2,0,0,0,0,0,5,0);
  returned = add_to_series(series, 65);
  TEST_CHAR_SERIES(series,2,2,2,0,0,0,0,0,6,0);

  // symbols[3]
  returned = add_to_series(series, 97);
  TEST_CHAR_SERIES(series,2,2,2,2,0,0,0,0,7,0);
  returned = add_to_series(series, 97);
  TEST_CHAR_SERIES(series,2,2,2,2,0,0,0,0,8,0);
  
  // symbols[4]
  returned = add_to_series(series, 129);
  TEST_CHAR_SERIES(series,2,2,2,2,2,0,0,0,9,0);
  returned = add_to_series(series, 129);
  TEST_CHAR_SERIES(series,2,2,2,2,2,0,0,0,10,0);
  
  // symbols[5]
  returned = add_to_series(series, 161);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,0,0,11,0);
  returned = add_to_series(series, 161);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,0,0,12,0);
  
  // symbols[6]
  returned = add_to_series(series, 193);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,0,13,0);
  returned = add_to_series(series, 193);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,0,14,0);
  
  // symbols[7]
  returned = add_to_series(series, 225);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,2,15,0);
  returned = add_to_series(series, 225);
  TEST_CHAR_SERIES(series,2,2,2,2,2,2,2,2,16,0);
}

TEST(add_to_series, border_values){
  char_series* series = new char_series;
  series->symbols[0] = 0; 
  series->symbols[1] = 0; 
  series->symbols[2] = 0; 
  series->symbols[3] = 0; 
  series->symbols[4] = 0; 
  series->symbols[5] = 0; 
  series->symbols[6] = 0; 
  series->symbols[7] = 0; 
  series->count = 0; 
  series->len = 0; 

  unsigned int max = 0x80000001;
  // symbols[0]
  int returned = add_to_series(series, 0);
  TEST_CHAR_SERIES(series,1,0,0,0,0,0,0,0,1,0);
  returned = add_to_series(series, 31);
  TEST_CHAR_SERIES(series,max,0,0,0,0,0,0,0,2,0);
  
  // symbols[1]
  returned = add_to_series(series, 32);
  TEST_CHAR_SERIES(series,max,1,0,0,0,0,0,0,3,0);
  returned = add_to_series(series, 63);
  TEST_CHAR_SERIES(series,max,max,0,0,0,0,0,0,4,0);

  // symbols[2]
  returned = add_to_series(series, 64);
  TEST_CHAR_SERIES(series,max,max,1,0,0,0,0,0,5,0);
  returned = add_to_series(series, 95);
  TEST_CHAR_SERIES(series,max,max,max,0,0,0,0,0,6,0);
  
  // symbols[3]
  returned = add_to_series(series, 96);
  TEST_CHAR_SERIES(series,max,max,max,1,0,0,0,0,7,0);
  returned = add_to_series(series, 127);
  TEST_CHAR_SERIES(series,max,max,max,max,0,0,0,0,8,0);
  
  // symbols[4]
  returned = add_to_series(series, 128);
  TEST_CHAR_SERIES(series,max,max,max,max,1,0,0,0,9,0);
  returned = add_to_series(series, 159);
  TEST_CHAR_SERIES(series,max,max,max,max,max,0,0,0,10,0);
  
  // symbols[5]
  returned = add_to_series(series, 160);
  TEST_CHAR_SERIES(series,max,max,max,max,max,1,0,0,11,0);
  returned = add_to_series(series, 191);
  TEST_CHAR_SERIES(series,max,max,max,max,max,max,0,0,12,0);
  
  // symbols[6]
  returned = add_to_series(series, 192);
  TEST_CHAR_SERIES(series,max,max,max,max,max,max,1,0,13,0);
  returned = add_to_series(series, 223);
  TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,0,14,0);
  
  // symbols[7]
  returned = add_to_series(series, 224);
  TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,1,15,0);
  returned = add_to_series(series, 255);
  TEST_CHAR_SERIES(series,max,max,max,max,max,max,max,max,16,0);
}