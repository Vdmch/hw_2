// Copyright [year] <Copyright Owner>

#pragma once

// Очистка памяти от all_series_array
#define free_series_array(array) \
            free(array->series); \
            free(array)

// хранит информацию о:

typedef struct __attribute((aligned(64))){
  unsigned int len;         // Длина серии символов
  unsigned int count;       // Количество серий этой длины
  unsigned int symbols[8];  // Информация о символах в серии
} char_series;                // 4 * 8 * 8 = 256 бит, каждый бит - отдельный символ

typedef struct{
    int length;             // Количество записанных серий char_series
    int size;               // Разамер выделенной памяти (в char_series)
    char_series* series;    // Указатель на массив с char_series
} all_series_array;           // сортируется по убыванию количества серий

int set_symbols_bit(unsigned char symbol, unsigned int* symbols);
int zero_series(char_series* series);
int process_series(all_series_array* series_array, unsigned int length, const unsigned int* symbols, int count);
all_series_array* count_series(char* symb_array, int len);
char get_first_printable_char(char_series* series);
