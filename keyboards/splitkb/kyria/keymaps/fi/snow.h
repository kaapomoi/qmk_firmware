#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef OLED_DRIVER_ENABLE
#include "oled_driver.h"
#include <avr/pgmspace.h>
#endif

#define DELTATIME 0.2f

#define MIN_X 0
#define MIN_Y 0
#define MAX_X 127
#define MAX_Y 63
#define MIN_MASS 1
#define MAX_MASS 3

#define VARIANCE 10

typedef struct {
    int16_t x;
    int16_t y;
} ivec2_t;

typedef struct {
    float x;
    float y;
} fvec2_t;

struct Snowflake
{
    fvec2_t pos;
    fvec2_t vel;
    float   mass;
};

struct Wind
{
    fvec2_t vel;
    fvec2_t acc;
};

void pixel_render_func(uint8_t *data, void *user_args);

ivec2_t ivec2(int8_t x, int8_t y);

fvec2_t fvec2(float x, float y);

int8_t round_f(float x);

void snow_animate(void);

void snow_init(uint32_t seed);