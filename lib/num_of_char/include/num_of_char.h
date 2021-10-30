// Copyright [year] <Copyright Owner>

#pragma once

#define free_series_array(array) \
            free(array->series); \
            free(array)

typedef struct {
  unsigned int len;
  unsigned int count;
  unsigned int symbols[8];
} char_series;

typedef struct {
    char_series* series;
    int length;
    int size;
} all_series_array;

all_series_array* count_series(char* symb_array, int len);
char get_first_printable_char(char_series* series);
