#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef OLED_DRIVER_ENABLE
#include "oled_driver.h"
#include <avr/pgmspace.h>
#endif

#define DELTATIME 0.05f

#define MIN_X 0
#define MIN_Y 0
#define MAX_X 127
#define MAX_Y 63

typedef struct {
    int8_t x;
    int8_t y;
} ivec2_t;

typedef struct {
    float x;
    float y;
} fvec2_t;

struct Particle
{
    fvec2_t pos;
    fvec2_t c_pos;
    float orbitv;
    float angle;
    float radius;
};

void pixel_render_func(uint8_t *data, void *user_args);

ivec2_t ivec2(int8_t x, int8_t y);

fvec2_t fvec2(float x, float y);

float weighted_rand(int8_t low, int8_t high, float falloff);

int8_t round_f(float x);

void solaris_animate(void);

void solaris_init(uint32_t seed);