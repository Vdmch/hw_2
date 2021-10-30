#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "num_of_char.h"
#include "test_lib_funcs.h"
}


#define TEST_CHAR_SERIES(series, symbols_0, symbols_1, symbols_2, symbols_3, symbols_4, symbols_5, symbols_6, symbols_7, count_num, len_num) \
            ASSERT_EQ(returned, 0); \
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

TEST(zero_series, test){
  char_series* series = new char_series;
  series->symbols[0] = 25; 
  series->symbols[1] = 7; 
  series->symbols[2] = 8; 
  series->symbols[3] = 52; 
  series->symbols[4] = 7582; 
  series->symbols[5] = 7; 
  series->symbols[6] = 2623; 
  series->symbols[7] = 57; 
  series->count = 2; 
  series->len = 157; 


  int returned = zero_series(NULL);
  EXPECT_EQ(returned, -1);
  
  returned = zero_series(series);
  TEST_CHAR_SERIES(series,0,0,0,0,0,0,0,0,0,0);

  delete(series);
}


TEST(add_to_series, nan_return){
  int returned = add_to_series(NULL, 'a');
  EXPECT_EQ(returned, -1);
}

TEST(add_to_series, correct_adding){
  char_series* series = new char_series;

  zero_series(series);

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
  delete(series);
}

TEST(add_to_series, border_values){
  char_series* series = new char_series;
  
  zero_series(series);

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

  delete(series);
}


TEST(find_insert_pos, nan_values){
  all_series_array *series_array = new all_series_array;
  series_array->size=100;
  series_array->length=0;
  series_array->series = (char_series*)malloc(sizeof(char_series) * 100);

  EXPECT_EQ(find_insert_pos(NULL, 1), -1);
  EXPECT_EQ(find_insert_pos(series_array, 1), 0);

  free(series_array->series);
  delete(series_array);
}

TEST(find_insert_pos, correct_pos){
  all_series_array *series_array = new all_series_array;
  char_series array[10];
  unsigned int lengths[10] = {2,4,5,6,7,10,11,12,29,100};
  for(int i = 0; i < 10; i++) array[i].len = lengths[i];
  series_array->series = array;
  series_array->length = 10;

  EXPECT_EQ(find_insert_pos(series_array, 1), 0);
  EXPECT_EQ(find_insert_pos(series_array, 2), 0);
  EXPECT_EQ(find_insert_pos(series_array, 4), 1);
  EXPECT_EQ(find_insert_pos(series_array, 8), 5);
  EXPECT_EQ(find_insert_pos(series_array, 29), 8);
  EXPECT_EQ(find_insert_pos(series_array, 100), 9);
  EXPECT_EQ(find_insert_pos(series_array, 110), 10);
  
  delete(series_array);
}


TEST(prepare_series_array, wrong_values){
  all_series_array* series_array = new all_series_array;
  series_array->length = 500;
  series_array->size = 100;
  series_array->series = (char_series*)malloc(sizeof(char_series) * 100);

  int result = prepare_series_array(NULL);
  EXPECT_EQ(result, -1);
  
  result = prepare_series_array(series_array);
  EXPECT_EQ(result, -3);

  free(series_array->series);
  delete(series_array);
}

TEST(prepare_series_array, memory_alloc){
  all_series_array* series_array = new all_series_array;
  series_array->series = NULL;
  series_array->size=0;
  series_array->length=0;

  int result = prepare_series_array(series_array);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(series_array->size, 100);
  if(series_array->series == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 211);
  
  series_array->length=99;
  result = prepare_series_array(series_array);
  EXPECT_EQ(result, 0);
  EXPECT_EQ(series_array->size, 200);
  if(series_array->series == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 217);

  free(series_array->series);
  delete(series_array);
}


TEST(commit_series, wrong_values){
  int result = commit_series(NULL, 1,1,1);
  EXPECT_EQ(result, -1);
}

TEST(commit_series, adding_values){

  all_series_array* series_array = new all_series_array;
  series_array->series = NULL;
  series_array->size=0;
  series_array->length=0;

  prepare_series_array(series_array);

  int returned = commit_series(series_array, 0,4,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 1);
  TEST_CHAR_SERIES((&series_array->series[0]),1,0,0,0,0,0,0,0,1,4);

  returned = commit_series(series_array, 0,4,1);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 1);
  TEST_CHAR_SERIES((&series_array->series[0]),3,0,0,0,0,0,0,0,2,4);
  
  returned = commit_series(series_array, 0,2,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 2);
  TEST_CHAR_SERIES((&series_array->series[0]),1,0,0,0,0,0,0,0,1,2);
  
  returned = commit_series(series_array, 2,6,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 3);
  TEST_CHAR_SERIES((&series_array->series[2]),1,0,0,0,0,0,0,0,1,6);

  returned = commit_series(series_array, 2,5,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 4);

  commit_series(series_array, 0,2,2);
  commit_series(series_array, 1,4,2);
  commit_series(series_array, 2,5,2);
  commit_series(series_array, 3,6,2);

  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 4);

  TEST_CHAR_SERIES((&series_array->series[0]),5,0,0,0,0,0,0,0,2,2);
  TEST_CHAR_SERIES((&series_array->series[1]),7,0,0,0,0,0,0,0,3,4);
  TEST_CHAR_SERIES((&series_array->series[2]),5,0,0,0,0,0,0,0,2,5);
  TEST_CHAR_SERIES((&series_array->series[3]),5,0,0,0,0,0,0,0,2,6);

  free(series_array->series);
  delete(series_array);
}

TEST(process_series, wrong_values){
  all_series_array* series_array = new all_series_array;
  series_array->length = 500;
  series_array->size = 100;
  series_array->series = (char_series*)malloc(sizeof(char_series) * 100);

  int result = process_series(NULL, 1,1);
  EXPECT_EQ(result, -100);
  
  result = process_series(series_array, 1,1);
  EXPECT_EQ(result, -3);

  free(series_array->series);
  delete(series_array);
}

TEST(process_series, adding_values){

  all_series_array* series_array = new all_series_array;
  series_array->series = NULL;
  int returned = process_series(series_array, 4,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 1);
  TEST_CHAR_SERIES((&series_array->series[0]),1,0,0,0,0,0,0,0,1,4);

  returned = process_series(series_array, 4,1);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 1);
  TEST_CHAR_SERIES((&series_array->series[0]),3,0,0,0,0,0,0,0,2,4);
  
  returned = process_series(series_array, 2,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 2);
  TEST_CHAR_SERIES((&series_array->series[0]),1,0,0,0,0,0,0,0,1,2);
  
  returned = process_series(series_array, 6,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 3);
  TEST_CHAR_SERIES((&series_array->series[2]),1,0,0,0,0,0,0,0,1,6);

  returned = process_series(series_array, 5,0);
  EXPECT_EQ(returned, 0);
  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 4);

  process_series(series_array, 2,2);
  process_series(series_array, 4,2);
  process_series(series_array, 5,2);
  process_series(series_array, 6,2);

  EXPECT_EQ(series_array->size, 100);
  EXPECT_EQ(series_array->length, 4);

  TEST_CHAR_SERIES((&series_array->series[0]),5,0,0,0,0,0,0,0,2,2);
  TEST_CHAR_SERIES((&series_array->series[1]),7,0,0,0,0,0,0,0,3,4);
  TEST_CHAR_SERIES((&series_array->series[2]),5,0,0,0,0,0,0,0,2,5);
  TEST_CHAR_SERIES((&series_array->series[3]),5,0,0,0,0,0,0,0,2,6);

  free(series_array->series);
  delete(series_array);
}


TEST(count_series, wrong_values){
  all_series_array* result = count_series(NULL, 2);
  if(result != NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 360);
  
  char tst_string[] = "abcd";
  result = count_series(tst_string, -3);
  if(result != NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 363);
}

TEST(count_series, adding_values){
  char tst_string[] = "abbcccccdddqqqef";
  all_series_array* result = count_series(tst_string, sizeof(tst_string));
  if(result == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 370);
  
  EXPECT_EQ(result->size, 100);
  EXPECT_EQ(result->length, 3);
  int returned = 0;

  TEST_CHAR_SERIES((&result->series[0]),0,0,0,0x00000004,0,0,0,0,1,2);
  TEST_CHAR_SERIES((&result->series[1]),0,0,0,0x00020010,0,0,0,0,2,3);
  TEST_CHAR_SERIES((&result->series[2]),0,0,0,0x00000008,0,0,0,0,1,5);

  free(result->series);
  free(result);
}

TEST(count_series, zero_string){
  char tst_string[] = "\0\0\0\0\0\0\0";
  all_series_array* result = count_series(tst_string, sizeof(tst_string));
  if(result == NULL) ADD_FAILURE_AT("num_of_char/tests/sec/test_func.cpp", 370);
  
  EXPECT_EQ(result->size, 100);
  EXPECT_EQ(result->length, 1);
  int returned = 0;

  TEST_CHAR_SERIES((&result->series[0]),1,0,0,0,0,0,0,0,1,sizeof(tst_string));

  free(result->series);
  free(result);
}

TEST(get_first_printable_char, test){
  char result = get_first_printable_char(NULL);
  EXPECT_EQ(result, 0);
  
  char_series* series = new char_series;
  zero_series(series);
  add_to_series(series, 'w');

  result = get_first_printable_char(series);
  EXPECT_EQ(result, 'w');

  zero_series(series);
  add_to_series(series, 'W');

  result = get_first_printable_char(series);
  EXPECT_EQ(result, 'W');

  delete(series);
}
