#pragma once

#include "snow.h"

enum dir{
    E_UP = 0,
    E_DOWN,
    E_LEFT,
    E_RIGHT
};

struct etch_cursor
{
    ivec2_t pos;
    bool white;
};

void clamp(int16_t *v, int16_t min, int16_t max);

void etch_move_cursor(enum dir d);

void etch_reset(void);

void etch_init(void);

void etch_animate(void);




