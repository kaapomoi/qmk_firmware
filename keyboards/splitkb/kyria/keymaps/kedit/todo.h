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

void todo_init(char* data, int buffer_size);

bool todo_handle_input(uint16_t keycode, keyrecord_t *record);

void todo_render(void);

enum todo_char {
    TC_A = 97,
    TC_B,
    TC_C,
    TC_D,
    TC_E,
    TC_F,
    TC_G,
    TC_H,
    TC_I,
    TC_J,
    TC_K,
    TC_L,
    TC_M,
    TC_N,
    TC_O,
    TC_P,
    TC_Q,
    TC_R,
    TC_S,
    TC_T,
    TC_U,
    TC_V,
    TC_W,
    TC_X,
    TC_Y,
    TC_Z,
    TC_PLUS,
    TC_MINS,
    TC_QUOT,
    TC_NUBS,
    TC_COMM,
    TC_DOT,
    TC_COLN,
    TC_SLSH,
    TC_BKSP
}; 