#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//#include "count_series.h"
#include "num_of_char.h"

#define MAX_CHAR_FOR_NUMBER 20
#define MAX_CHAR_FOR_OTHER 50

char_series* find_most_frequent_series(all_series_array* series_array) {
  if (series_array == NULL) return NULL;
  if (series_array->length <= 0) return NULL;

  int max_count = 0;
  int max_count_index = 0;
  for (int i = 0; i < series_array->length; i++) {
    int sel_count = series_array->series[i].count;
    if (sel_count > max_count) {
      max_count = sel_count;
      max_count_index = i;
    }
  }
  return &series_array->series[max_count_index];
}

all_series_array* count_all_series(char* char_array, int size) {
  long cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (cpu_core_count <= 0) return NULL;
  printf("cpu core count: %ld\n", cpu_core_count);

  int(*fd)[2] = (int(*)[2])malloc(cpu_core_count * sizeof(int[2]));
  pid_t* pids = (int*)malloc(cpu_core_count * sizeof(int));

  if (!fd || !pids) {
    if (fd) free(fd);
    if (pids) free(pids);
    return NULL;
  }

  int step_size = size / cpu_core_count;
  char* sel_addr = char_array;

  for (int i = 0; i < cpu_core_count; i++) {
    if (pipe(fd[i]) == -1) {
      free(fd);
      free(pids);
      return NULL;
    }
    pids[i] = fork();
    if (pids[i] == -1) {
      free(fd);
      free(pids);
      return NULL;
    } else if (pids[i] == 0) {
      sel_addr = sel_addr + step_size * i;
      if (i == cpu_core_count - 1) step_size = char_array + size - sel_addr;

      close(fd[i][0]);
      all_series_array* series_array = NULL;
      series_array = count_series(sel_addr, step_size);

      if (series_array == NULL) {
        free(fd);
        free(pids);
        exit(1);
      }

      int bytes_to_write = series_array->size * sizeof(char_series);
      long unsigned int result = 0;
      result += write(fd[i][1], (char*)series_array, sizeof(all_series_array));
      result += write(fd[i][1], (char*)series_array->series, bytes_to_write);
      free_series_array(series_array);
      free(fd);
      free(pids);
      if (result == bytes_to_write + sizeof(all_series_array))
        exit(0);
      else{
        exit(1);
      }
    }
    close(fd[i][1]);
  }

  all_series_array* series_array =
      (all_series_array*)malloc(sizeof(all_series_array) * cpu_core_count);

  for (int i = 0; i < cpu_core_count; i++) {
    int status = 0;
    waitpid(pids[i], &status, 0);
    if ((status != 0)) {
      free(fd);
      free(pids);
      for (int k = 0; k < i; k++) free(series_array[k].series);
      free(series_array);
      return NULL;
    }
    int result =
        read(fd[i][0], (char*)&series_array[i], sizeof(all_series_array));
    if (result != sizeof(all_series_array)) {
      free(fd);
      free(pids);
      for (int k = 0; k < i; k++) free(series_array[k].series);
      free(series_array);
      return NULL;
    }

    int bytes_to_read = series_array[i].size * sizeof(char_series);
    char_series* series = (char_series*)malloc(bytes_to_read);

    if (series == NULL) {
      free(fd);
      free(pids);
      for (int k = 0; k < i; k++) free(series_array[k].series);
      free(series_array);
      return NULL;
    }

    result = read(fd[i][0], (char*)series, bytes_to_read);
    series_array[i].series = series;
    if (result != bytes_to_read) {
      free(fd);
      free(pids);
      for (int k = 0; k < i; k++) free(series_array[k].series);
      free(series_array);
      return NULL;
    }
  }
  free(fd);
  free(pids);
  return series_array;
}

all_series_array* combine_arrays(all_series_array* series_array) {
  long cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (cpu_core_count <= 0) return NULL;
  int total_length = 0;

  for (int i = 0; i < cpu_core_count; i++) {
    total_length += series_array[i].length;
  }

  all_series_array* result_array =
      (all_series_array*)malloc(sizeof(all_series_array));
  char_series* result_series =
      (char_series*)malloc(sizeof(char_series) * total_length);

  if (!result_array || !result_series) {
    if (result_array) free(result_array);
    if (result_series) free(result_series);
    return NULL;
  }

  result_array->series = result_series;
  result_array->size = total_length;
  result_array->length = 0;

  if (total_length == cpu_core_count) {
    process_series(result_array, series_array[0].series[0].len,
                   series_array[0].series[0].symbols,
                   series_array[0].series[0].count);
    for (int i = 1; i < cpu_core_count; i++) {
      result_array->series[0].len += series_array[i].series[0].len;
    }
  } else {
    for (int i = 0; i < cpu_core_count; i++) {
      for (int k = 0; k < series_array[i].length; k++) {
        process_series(result_array, series_array[i].series[k].len,
                       series_array[i].series[k].symbols,
                       series_array[i].series[k].count);
      }
    }
  }
  return result_array;
}

char* get_most_frequent_series(char* char_array, int size) {
  if (char_array == NULL) return NULL;
  long cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);

  all_series_array* series_array = count_all_series(char_array, size);
  if (series_array == NULL) return NULL;

  all_series_array* combined_series_array = combine_arrays(series_array);
  if (combined_series_array == NULL) {
    for (int i = 0; i < cpu_core_count; i++) free(series_array[i].series);
    free(series_array);
    return NULL;
  }

  char_series* most_frequent_series =
      find_most_frequent_series(combined_series_array);
  if (most_frequent_series == NULL) {
    for (int i = 0; i < cpu_core_count; i++) free(series_array[i].series);
    free(series_array);
    free_series_array(combined_series_array);
    return NULL;
  }
  int length = most_frequent_series->len;
  int count = most_frequent_series->count;
  char char_to_print = get_first_printable_char(most_frequent_series);

  char* result = (char*)malloc(sizeof(char) *
                               (2 * MAX_CHAR_FOR_NUMBER + MAX_CHAR_FOR_OTHER));
  assert(result != NULL);
  if (char_to_print == '\0')
    sprintf(result, "most frequent series: '%s' x %i   (%i times)\n", "\\0",
            length, count);
  else
    sprintf(result, "most frequent series: '%c' x %i   (%i times)\n",
            char_to_print, length, count);

  for (int i = 0; i < cpu_core_count; i++) free(series_array[i].series);
  free(series_array);

  free_series_array(combined_series_array);

  return result;
}
