#include "solaris.h"

#define MAX_PARTICLES 32

struct Particle particles[MAX_PARTICLES];

int initialized = 0;

uint8_t pre_flake_byte = 0x10;

fvec2_t fvec2(float x, float y){
    fvec2_t res = {x,y};
    return res;
}

ivec2_t ivec2(int8_t x, int8_t y){
    ivec2_t res = {x, y};
    return res;
}

float weighted_rand(int8_t low, int8_t high, float falloff){
    float cutoff = 1.0f;

    for(int8_t i = 0; i < 10; i++){
        int8_t random = rand()% high; 
        if ((high - random) <= ((high - low) * cutoff))
        {
            return random;
        }
        cutoff += falloff;
    }
    
    return low;
}

void pixel_render_func(uint8_t *data, void *user_args) {
    uint8_t flake = *(uint8_t*)user_args;
    pre_flake_byte = *data;
    *data |= flake;
}

int8_t round_f(float x)
{
    return x/1;
}

void solaris_init(uint32_t seed){
    if (initialized == 0){
        srand(seed);
        for (int16_t i = 0; i < MAX_PARTICLES; i++) {
            particles[i].pos = fvec2( 10, 10);
            particles[i].c_pos = fvec2( 50, 10);
            particles[i].radius = 10;
            particles[i].orbitv = 1.0f;
            particles[i].angle = (rand()%360) / 3.141592f;
        }
        initialized = 1;
    }  
}

void solaris_animate(void){

    for (int8_t i = 0; i < MAX_PARTICLES; i++)
    {
        // Clear old pixel 
        fvec2_t old_pos = particles[i].pos;
        oled_write_pixel(round_f(old_pos.x), round_f(old_pos.y), false);

        // Calculate new pixel position
        particles[i].angle -= particles[i].orbitv * DELTATIME;
        particles[i].pos.x = particles[i].c_pos.x + particles[i].radius * cosf(particles[i].angle);
        particles[i].pos.y = particles[i].c_pos.y + particles[i].radius * sinf(particles[i].angle);

        // Write new pixel position
        if (particles[i].pos.x < 0){
            continue;
        } else if (particles[i].pos.x > MAX_X){
            continue;
        } else if (particles[i].pos.y > MAX_Y){
            continue;
        } else if (particles[i].pos.y < 0){
            continue;
        } else {
            uint8_t line = round_f(particles[i].pos.y) / 8;
            uint8_t sub_pos = round_f(particles[i].pos.y) % 8;
            uint8_t flake_byte = 0b00000001 << sub_pos;
            oled_byte_apply_func(particles[i].pos.x, line, pixel_render_func, &flake_byte);
        }
    }
}

