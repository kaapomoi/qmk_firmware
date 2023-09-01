#include "snow.h"


#define MAX_FLAKES 24

static const float G = 9.81;

struct Snowflake flakes[MAX_FLAKES];
struct Wind wind;

int initialized = 0;

volatile float wind_counter = 0.0f;

uint8_t pre_flake_byte = 0x10;

fvec2_t fvec2(float x, float y){
    fvec2_t res = {x,y};
    return res;
}

ivec2_t ivec2(int8_t x, int8_t y){
    ivec2_t res = {x, y};
    return res;
}

void pixel_render_func(uint8_t *data, void *user_args) {
    uint8_t flake = *(uint8_t*)user_args;
    pre_flake_byte = *data;
    *data |= flake;
}

uint8_t round_f(float x)
{
    return (uint8_t)round(x);
}

void snow_init(uint32_t seed){
    if (initialized == 0){
        srand(seed);
        for (int16_t i = 0; i < MAX_FLAKES; i++) {
            flakes[i].pos = fvec2( rand()%MAX_X, 0);
            flakes[i].vel = fvec2((rand()%200 - 100) * 0.01, rand()%100 * 0.01);
            flakes[i].mass = rand()%MAX_MASS + MIN_MASS;
        }
        wind.acc = fvec2(0,0);
        wind.vel = fvec2(0,0);
        initialized = 1;
    }
}

void snow_animate(void){

    wind_counter += 0.1f * 3.1415f;

    fvec2_t windv = {sinf(wind_counter*0.5f) + sinf(wind_counter*0.25f) + sinf(wind_counter*0.1f), sinf(wind_counter*0.2f + 1)};

    for (int16_t i = 0; i < MAX_FLAKES; i++)
    {
        float effectiveness = rand()% VARIANCE * 0.1f;
        fvec2_t old_pos = flakes[i].pos;

        flakes[i].vel.x += effectiveness * windv.x * 0.5f * DELTATIME / flakes[i].mass;
        flakes[i].vel.y += effectiveness * windv.y * 0.2f * DELTATIME / flakes[i].mass;

        flakes[i].vel.y += G * flakes[i].mass * 0.005f * DELTATIME;
        flakes[i].pos.x += flakes[i].vel.x * DELTATIME;
        flakes[i].pos.y += flakes[i].vel.y * DELTATIME;

        oled_write_pixel(round_f(old_pos.x), round_f(old_pos.y), false);
        if (flakes[i].pos.x < 0){
            flakes[i].pos.x = MAX_X;
        } else if (flakes[i].pos.x > MAX_X){
            flakes[i].pos.x = 0;
        } else if (flakes[i].pos.y > MAX_Y){
            flakes[i].pos.y = 0;
            flakes[i].vel = fvec2((rand()% 200 - 100) * 0.01, rand()%100 * 0.01);
        } else if (flakes[i].pos.y < 0){
            flakes[i].pos = fvec2(rand()% MAX_X, 0);
            flakes[i].vel = fvec2((rand()% 200 - 100) * 0.01, rand()%100 * 0.01);
        } else {
            uint8_t line = round_f(flakes[i].pos.y) / 8;
            uint8_t sub_pos = round_f(flakes[i].pos.y) % 8;
            uint8_t flake_byte = 0b00000001 << sub_pos;
            oled_byte_apply_func(flakes[i].pos.x, line, pixel_render_func, &flake_byte);
        }
    }
}

