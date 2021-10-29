
#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    unsigned int len;
    unsigned int count;
    unsigned int symbols[8];
} char_series;

int add_to_series(char_series* series, unsigned char symbol);
