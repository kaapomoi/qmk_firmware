#pragma once
#include "snow.h"

#define DRAWCHANCE 100
#define BOX_WIDTH 127
#define BOX_HEIGHT 63
#define BOX_TOP_LEFT_X 0
#define BOX_TOP_LEFT_Y 0
#define MAX_LINES_TILL_RESET 256

struct brush
{
    fvec2_t pos;
    fvec2_t vel;
    fvec2_t determ;
    float hardness_base;
    float hardness;
    float pressure_delta;
    float determ_pressure;
    ivec2_t size;
    int32_t stroke_len;
    bool white;
};

void brush_raise_hardness(void);
void brush_lower_hardness(void);

void brush_init(void);

void brush_animate(void);