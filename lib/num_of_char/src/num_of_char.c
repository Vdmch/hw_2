#include "num_of_char.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTTIAL_ARR_SIZE 10

// зануляет char_series
int zero_series(char_series* series) {
  if (series == NULL) return -1;

  series->len = 0;
  series->count = 0;
  int size = sizeof(series->symbols) / sizeof(series->symbols[0]);
  for (int i = 0; i < size; i++) series->symbols[i] = 0;

  return 0;
}

// Устанавливает соответствующий символу бит, предварительно зануляя память
int set_symbols_bit(unsigned char symbol, unsigned int* symbols) {
  if (symbols == NULL) return -1;
  size_t size = sizeof(int) * 8;
  unsigned int integer_part = symbol / size;
  unsigned int remainder = symbol - (integer_part * size);

  memset(symbols, 0, size);

  symbols[integer_part] |= 1 << remainder;
  return 0;
}

// Добавляет флаги символов в char_series->symbols,
// увеличивает счетчик кол-ва серий данной длины на count
int add_to_series(char_series* series, const unsigned int* symbols, int count) {
  if (series == NULL) return -1;
  if (symbols == NULL) return -1;
  for (int i = 0; i < 8; i++) series->symbols[i] |= symbols[i];
  series->count += count;
  return 0;
}

// Находим индекс char_series с заданной длиной series_length
// или индекс для вставки с помощью бинарного поиска
int find_insert_pos(all_series_array* series_array,
                    unsigned int series_length) {
  if (series_array == NULL) return -1;

  if (series_array->length == 0) return 0;

  int top = series_array->length;
  int bot = 0;

  if (series_length <= series_array->series[0].len) return 0;
  if (series_length > series_array->series[top - 1].len) return top;

  while (top != bot + 1) {
    int avr = (top + bot) / 2;
    unsigned int sel_length = series_array->series[avr].len;
    if (sel_length >= series_length)
      top = avr;
    else
      bot = avr;
  }
  return top;
}

// Выделяет память для series_array->series в случае если:
//    - all_series_array был только что создан и память не инициализирована
//    - выделенная память заканчивается
int prepare_series_array(all_series_array* series_array) {
  if (series_array == NULL) return -1;

  if (series_array->series == NULL) {
    series_array->series =
        (char_series*)malloc(sizeof(char_series) * INTTIAL_ARR_SIZE);

    if (series_array->series == NULL) return -2;

    series_array->size = INTTIAL_ARR_SIZE;
    series_array->length = 0;
  }

  if (series_array->length >= series_array->size) return -3;

  if (series_array->length == series_array->size - 1) {
    char_series* new_array = (char_series*)realloc(
        series_array->series, sizeof(char_series) * series_array->size * 2);
    if (new_array == NULL) return -4;

    series_array->series = new_array;
    series_array->size *= 2;
  }
  return 0;
}

// В all_series_array по заданному индексу добавляет к серии
// (или создает новую если заданная длина не совпадает с серией по заданному
// индексу) Флаги символов и увеличивает счетчик данной серии на count
int commit_series(all_series_array* series_array, int pos, unsigned int length,
                  const unsigned int* symbols, int count) {
  if (series_array == NULL) return -1;

  char_series* sel_series = &series_array->series[pos];
  if (pos >= series_array->length) {
    zero_series(sel_series);
    sel_series->len = length;
    series_array->length++;
  }

  else if (sel_series->len != length) {
    size_t to_copy = sizeof(char_series) * (series_array->length - pos);
    memmove(sel_series + 1, sel_series, to_copy);
    zero_series(sel_series);

    sel_series->len = length;
    series_array->length++;
  }

  int result = add_to_series(sel_series, symbols, count);
  return result;
}

//
//
//
int process_series(all_series_array* series_array, unsigned int length,
                   const unsigned int* symbols, int count) {
  if (series_array == NULL) return -100;
  if (symbols == NULL) return -200;

  int result = prepare_series_array(series_array);
  if (result != 0) return result;

  int pos = find_insert_pos(series_array, length);

  commit_series(series_array, pos, length, symbols, count);
  return 0;
}

all_series_array* count_series(char* symb_array, int len) {
  if ((symb_array == NULL) || (len <= 0)) return NULL;

  all_series_array* series_array =
      (all_series_array*)malloc(sizeof(all_series_array));
  if (series_array == NULL) return NULL;

  series_array->series = NULL;

  char prev_symbol = symb_array[0];
  int series_len = 1;
  unsigned int symbols[8];
  for (int i = 1; i < len; i++) {
    char sel_symbol = symb_array[i];
    if (prev_symbol == sel_symbol) {
      series_len++;
      if (i + 1 == len) {
        if (set_symbols_bit(prev_symbol, symbols) != 0) {
          free_series_array(series_array);
          return NULL;
        }
        int result = process_series(series_array, series_len, symbols, 1);
        series_len = 1;

        if (result != 0) {
          free_series_array(series_array);
          return NULL;
        }
      }
    } else {
      if (series_len > 1) {
        if (set_symbols_bit(prev_symbol, symbols) != 0) {
          free_series_array(series_array);
          return NULL;
        }
        int result = process_series(series_array, series_len, symbols, 1);
        series_len = 1;

        if (result != 0) {
          free_series_array(series_array);
          return NULL;
        }
      }
      prev_symbol = sel_symbol;
    }
  }
  return series_array;
}

char get_first_printable_char(char_series* series) {
  if (series == NULL) return 0;

  unsigned int sel_symbols = series->symbols[3];

  for (char i = 'a'; i <= 'z'; i++) {
    if ((sel_symbols >> (i - 96)) & 0x1) return i;
  }

  sel_symbols = series->symbols[2];
  for (char i = 'A'; i <= 'Z'; i++) {
    if ((sel_symbols >> (i - 64)) & 0x1) return i;
  }
  return 0;
}
