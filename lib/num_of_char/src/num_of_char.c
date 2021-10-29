// Copyright [year] <Copyright Owner>

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    unsigned int len;
    unsigned int count;
    unsigned int symbols[8];
} char_series;

int add_to_series(char_series* series, unsigned char symbol){
    if(series == NULL) return -1;
    unsigned int size = sizeof(series->symbols[0]) * 8;
    unsigned int integer_part = symbol / size;
    unsigned int remainder = symbol - (integer_part * size);

    series->symbols[integer_part] |= 1 << remainder;
    series->count++;
    return 0;
}

