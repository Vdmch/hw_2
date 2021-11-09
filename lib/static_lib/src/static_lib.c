#include <stdio.h>
#include <stdlib.h>

#include "count_series.h"
#include "num_of_char.h"

#define MAX_CHAR_FOR_NUMBER 20
#define MAX_CHAR_FOR_OTHER 50

// В переданном массиве символов находит все серии, символы в них и число серий
// каждой длины Возвращает строку с описанием наиболее распространенной серии
char* get_most_frequent_series(char* char_array, int size) {
  all_series_array* series_array = count_series(char_array, size);
  if (series_array == NULL) return NULL;

  char_series* most_frequent_series = find_most_frequent_series(series_array);
  if (most_frequent_series == NULL) {
    return NULL;
  }
  int length = most_frequent_series->len;
  int count = most_frequent_series->count;
  char char_to_print = get_first_printable_char(most_frequent_series);

  char* result = (char*)malloc(sizeof(char) *
                               (2 * MAX_CHAR_FOR_NUMBER + MAX_CHAR_FOR_OTHER));
  if (result == NULL) {
    free_series_array(series_array);
    return NULL;
  }
  if (char_to_print == '\0')
    sprintf(result, "most frequent series: '%s' x %i   (%i times)\n", "\\0",
            length, count);
  else
    sprintf(result, "most frequent series: '%c' x %i   (%i times)\n",
            char_to_print, length, count);

  free_series_array(series_array);

  return result;
}
