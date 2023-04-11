#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include QMK_KEYBOARD_H

#include "oled_driver.h"
#include <avr/pgmspace.h>

#define MIN_X 0
#define MIN_Y 0
#define MAX_X 127
#define MAX_Y 63

typedef struct {
    int16_t x;
    int16_t y;
} ivec2_t;

void todo_init(char* data, int buffer_size);

void todo_handle_input(uint16_t keycode, keyrecord_t *record);

void todo_render(void);

