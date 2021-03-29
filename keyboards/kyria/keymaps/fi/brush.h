#pragma once
#include "snow.h"

#define DRAWCHANCE 100

struct brush
{
    fvec2_t pos;
    fvec2_t vel;
    fvec2_t determ;
    float hardness;
    float pressure_delta;
    ivec2_t size;
    int32_t stroke_len;
    bool white;
};

void brush_init(void);

void brush_animate(void);