#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "count_series.h"
#include "test_lib_funcs.h"
}

TEST(get_first_printable_char, test){
    all_series_array* series_array = count_series(NULL, 0);
    char_series* result = find_most_frequent_series(series_array);
    if(result != NULL) ADD_FAILURE_AT("shared_lib/tests/sec/test_func.cpp", 12);

    char tst_string[] = "abbcccccdddqqqef";
    series_array = count_series(tst_string, sizeof(tst_string));
    
    result = find_most_frequent_series(series_array);
    EXPECT_EQ(result->count, 2);
    EXPECT_EQ(result->len, 3);
    EXPECT_EQ(get_first_printable_char(result), 'd');

    free(series_array->series);
    free(series_array);
}



TEST(get_most_frequent_series, adding_values){
    char* result = get_most_frequent_series(NULL, 0);
    if(result != NULL) ADD_FAILURE_AT("shared_lib/tests/sec/test_func.cpp", 28);


    char tst_string[] = "bbaacqbbaaacfffqqsaaqcy";
    result = get_most_frequent_series(tst_string, sizeof(tst_string));
    
    EXPECT_STREQ(result, "most frequent series: 'a' x 2   (5 times)\n");
    free(result);


    char tst_string_2[] = "\0\0\0\0\0\0\0";
    result = get_most_frequent_series(tst_string_2, sizeof(tst_string_2));
    
    EXPECT_STREQ(result, "most frequent series: '\\0' x 8   (1 times)\n");
    free(result);
}
