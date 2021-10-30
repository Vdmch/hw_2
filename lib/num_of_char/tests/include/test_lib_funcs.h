#pragma once
#include <stdint.h>
#include <stdlib.h>

#include "num_of_char.h"

int zero_series(char_series* series);
int add_to_series(char_series* series, unsigned char symbol);
int find_insert_pos(all_series_array* series_array, unsigned int series_length);
int prepare_series_array(all_series_array* series_array);
int commit_series(all_series_array* series_array, unsigned int pos, unsigned int length, unsigned char symbol);
int process_series(all_series_array* series_array, unsigned int length, unsigned char symbol);
