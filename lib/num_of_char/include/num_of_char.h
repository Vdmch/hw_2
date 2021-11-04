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
    int length;
    int size;
    char_series* series;
} all_series_array;

int set_symbols_bit(unsigned char symbol, unsigned int* symbols);
int zero_series(char_series* series);
int process_series(all_series_array* series_array, unsigned int length, const unsigned int* symbols, int count);
all_series_array* count_series(char* symb_array, int len);
char get_first_printable_char(char_series* series);
