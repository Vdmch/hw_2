#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//#include "count_series.h"
#include "num_of_char.h"

#define MAX_CHAR_FOR_NUMBER 20
#define MAX_CHAR_FOR_OTHER 50


// Разбивает массив символов на несколько в зависимости от числа ядер процессора
// и передает их на обработку дочерним процессам.
int init_process(int (*fd)[2], int *pids, char* char_array, int size, long num_of_cores){
  
  int step_size = size / cpu_core_count;
  char* sel_addr = char_array;

  for (int i = 0; i < cpu_core_count; i++) {
    if (pipe(fd[i]) == -1) {
      free(fd);
      free(pids);
      return -1;
    }
    pids[i] = fork();
    if (pids[i] == -1) {
      free(fd);
      free(pids);
      return -1;
    } else if (pids[i] == 0) {
      sel_addr = sel_addr + step_size * i;
      if (i == cpu_core_count - 1) {
        step_size = char_array + size - sel_addr;
      }
      close(fd[i][0]);
      all_series_array* series_array = NULL;
      series_array = count_series(sel_addr, step_size);

      if (series_array == NULL) {
        free(fd);
        free(pids);
        exit(1);
      }

      int bytes_to_write = series_array->length * sizeof(char_series);
      long unsigned int result = 0;
      result += write(fd[i][1], (char*)series_array, sizeof(all_series_array));
      result += write(fd[i][1], (char*)series_array->series, bytes_to_write);
      close(fd[i][0]);

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
  return 0;
}

#define free_data(fd, pids, series_array, i) \
                          free(fd); \
                          free(pids); \
                          for (int k = 0; k < i; k++) free(series_array[k].series); \
                          free(series_array)

// Функция обрабоотки результатов от дочерних процессов
all_series_array* main_process(int (*fd)[2], int *pids, long num_of_cores){
  all_series_array* series_array =
      (all_series_array*)malloc(sizeof(all_series_array) * cpu_core_count);

  if(series_array == NULL){
    return NULL;
  }
  for (int i = 0; i < cpu_core_count; i++) {
    int status = 0;
    waitpid(pids[i], &status, 0);
    if ((status != 0)) {
      free_data(fd, pids, series_array, i);
      return NULL;
    }
    int result =
        read(fd[i][0], (char*)&series_array[i], sizeof(all_series_array));
    if (result != sizeof(all_series_array)) {
      return NULL;

    }

    int bytes_to_read = series_array[i].length * sizeof(char_series);
    char_series* series = (char_series*)malloc(bytes_to_read);

    if (series == NULL) {
      free_data(fd, pids, series_array, i);
      return NULL;
    }

    result = read(fd[i][0], (char*)series, bytes_to_read);
    series_array[i].series = series;
    if (result != bytes_to_read) {
      free_data(fd, pids, series_array, i);
      return NULL;
    }
    close(fd[i][0]);
  }
  
  free(fd);
  free(pids);
  return series_array;
}

// Создает дочерние процессы
// На выходе выдает массив с all_series_array от каждого процесса
all_series_array* count_all_series(char* char_array, int size) {
  long cpu_core_count = sysconf(_SC_NPROCESSORS_ONLN);
  if (cpu_core_count <= 0) return NULL;

  int(*fd)[2] = (int(*)[2])malloc(cpu_core_count * sizeof(int[2]));
  pid_t* pids = (int*)malloc(cpu_core_count * sizeof(int));

  if (!fd || !pids) {
    if (fd) free(fd);
    if (pids) free(pids);
    return NULL;
  }

  int result = init_process(fd, pids, char_array, size, cpu_core_count);
  if(result != 0) {
    free(fd);
    free(pids);
    return NULL;
  }

  all_series_array* series_array = main_process(fd, pids, cpu_core_count);

  return series_array;
}

// Их нескольких all_series_array собирает одну, совмещая информацию  
// о длинах серий, встречаемых символах и их количестве.
// Если во всех all_series_array по одной серии, то считает их 
// как одну и складывает их длины
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


// В переданном массиве символов находит все серии, символы в них и число серий каждой длины
// Возвращает строку с описанием наиболее распространенной серии
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
