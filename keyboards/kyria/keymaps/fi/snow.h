#pragma once

#define DELTATIME 0.2f

typedef struct {
    int32_t x;
    int32_t y;
} ivec2_t;

typedef struct {
    float x;
    float y;
} fvec2_t;

struct Snowflake
{
    fvec2_t pos;
    fvec2_t vel;
};

struct Wind
{
    fvec2_t vel;
    fvec2_t acc;
};


void snow_animate(void);

void snow_init(uint32_t seed);