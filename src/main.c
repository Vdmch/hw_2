#include <stdio.h>
#include <stdlib.h>

#include "count_series.h"

#define ARR_SIZE 104857600UL
int main(int argc, char* argv[]) {
  char* char_array = (char*)malloc(sizeof(char) * ARR_SIZE);
  if (char_array == NULL) return -1;

  char* result = get_most_frequent_series(char_array, ARR_SIZE);
  if (result == NULL) {
    free(char_array);
    printf("result is null\n");
    return -2;
  }
  printf("%s", result);
  free(char_array);
  free(result);
  return 0;
}
