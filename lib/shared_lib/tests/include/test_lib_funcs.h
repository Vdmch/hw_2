#pragma once
#include <stdint.h>
#include <stdlib.h>

#include "num_of_char.h"

char_series* find_most_frequent_series(all_series_array* series_array);
all_series_array* combine_arrays(all_series_array** series_array);
all_series_array** count_all_series(char* char_array, int size);
