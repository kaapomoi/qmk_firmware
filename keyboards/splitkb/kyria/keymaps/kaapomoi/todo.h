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

enum letter {
    to_a = SAFE_RANGE,
    to_b,
    to_c,
    to_d,
    to_e,
    to_f,
    to_g,
    to_h,
    to_i,
    to_j,
    to_k,
    to_l,
    to_m,
    to_n,
    to_o,
    to_q,
    to_p,
    to_r,
    to_s,
    to_t,
    to_u,
    to_v,
    to_w,
    to_x,
    to_y,
    to_z
};

typedef struct {
    int16_t x;
    int16_t y;
} ivec2_t;

void todo_init(char* data, int buffer_size);

void todo_handle_input(enum letter l);

void todo_render(void);

