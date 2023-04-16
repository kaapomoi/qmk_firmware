#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include QMK_KEYBOARD_H

#include "oled_driver.h"
#include <avr/pgmspace.h>

int clamp_cursor(int cursor);

int move_and_clamp_cursor(int cursor, int amount);

void todo_init(void);

bool todo_handle_input(uint16_t keycode, keyrecord_t *record);

void todo_render(void);

void render_cursor(void);

enum todo_char {
    TC_BKSP = 8,
    TC_ESC  = 27,
    TC_SPCE = 32,
    TC_EXLM,
    TC_QUOT,
    TC_HASH,
    TC_DOLR, 
    TC_PERC,
    TC_AMPR,
    TC_APOS,
    TC_OPAR,
    TC_CPAR,
    TC_ASTE,
    TC_PLUS,
    TC_COMM,
    TC_MINU,
    TC_PERI,
    TC_SLSH,
    TC_0,
    TC_1,
    TC_2,
    TC_3,
    TC_4,
    TC_5,
    TC_6,
    TC_7,
    TC_8,
    TC_9,
    TC_COLN,
    TC_SCOL,
    TC_LT,
    TC_EQ,
    TC_GT,
    TC_QUES,
    TC_AT,
    TC_A = 65,
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
    TC_OBRA = 91,
    TC_BKSL,
    TC_CBRA,
    TC_CARE,
    TC_UNDE,
    TC_GRAV,
    TC_OBRE = 123,
    TC_VBAR,
    TC_CRBE,
    TC_TILD,
    TC_DEL,
    TC_ENT = 128, /// Non-ASCII codes
    TC_LEFT,
    TC_DOWN,
    TC_UP,
    TC_RGHT
}; 

