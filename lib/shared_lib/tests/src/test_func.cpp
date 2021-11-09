#include <gtest/gtest.h>
#include <iostream>

extern "C" {
#include "count_series.h"
#include "test_lib_funcs.h"
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
