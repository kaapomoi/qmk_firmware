#include "solaris.h"

#define MAX_PARTICLES 16

struct Particle particles[MAX_PARTICLES];
struct Ring small_ring;
struct Ring big_ring;

int initialized = 0;
volatile int ring_draw_counter = 0;    

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

void draw_ring(struct Ring* ring){
    int radius = ring->radius;
    int r2 = radius * radius;
    draw_ring_pixel(ring->c_pos.x, ring->c_pos.y + radius, ring->n_th_pixel);
    draw_ring_pixel(ring->c_pos.x + radius, ring->c_pos.y, ring->n_th_pixel);
    draw_ring_pixel(ring->c_pos.x, ring->c_pos.y - radius, ring->n_th_pixel);
    draw_ring_pixel(ring->c_pos.x - radius, ring->c_pos.y, ring->n_th_pixel);

    int x = 1;
    int y = (int) (sqrt(r2 - 1) + 0.5);
    while (x < y){
        draw_ring_pixel(ring->c_pos.x + x, ring->c_pos.y + y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x + y, ring->c_pos.y + x, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x + x, ring->c_pos.y - y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - x, ring->c_pos.y + y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x + y, ring->c_pos.y - x, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - y, ring->c_pos.y + x, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - x, ring->c_pos.y - y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - y, ring->c_pos.y - x, ring->n_th_pixel);
        x += 1;
        y = (int) (sqrt(r2 - x*x) + 0.5);
    }
    if (x == y){
        draw_ring_pixel(ring->c_pos.x + x, ring->c_pos.y + y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - x, ring->c_pos.y + y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x + x, ring->c_pos.y - y, ring->n_th_pixel);
        draw_ring_pixel(ring->c_pos.x - x, ring->c_pos.y - y, ring->n_th_pixel);
    }
}

void clear_ring(struct Ring* ring){
    int radius = ring->radius;
    int r2 = radius * radius;
    clear_ring_pixel(ring->c_pos.x, ring->c_pos.y + radius);
    clear_ring_pixel(ring->c_pos.x, ring->c_pos.y - radius);
    clear_ring_pixel(ring->c_pos.x + radius, ring->c_pos.y);
    clear_ring_pixel(ring->c_pos.x - radius, ring->c_pos.y);

    int x = 1;
    int y = (int) (sqrt(r2 - 1) + 0.5);
    while (x < y){
        clear_ring_pixel(ring->c_pos.x + x, ring->c_pos.y + y);
        clear_ring_pixel(ring->c_pos.x + x, ring->c_pos.y - y);
        clear_ring_pixel(ring->c_pos.x - x, ring->c_pos.y + y);
        clear_ring_pixel(ring->c_pos.x - x, ring->c_pos.y - y);
        clear_ring_pixel(ring->c_pos.x + y, ring->c_pos.y + x);
        clear_ring_pixel(ring->c_pos.x + y, ring->c_pos.y - x);
        clear_ring_pixel(ring->c_pos.x - y, ring->c_pos.y + x);
        clear_ring_pixel(ring->c_pos.x - y, ring->c_pos.y - x);
        x += 1;
        y = (int) (sqrt(r2 - x*x) + 0.5);
    }
    if (x == y){
        clear_ring_pixel(ring->c_pos.x + x, ring->c_pos.y + y);
        clear_ring_pixel(ring->c_pos.x + x, ring->c_pos.y - y);
        clear_ring_pixel(ring->c_pos.x - x, ring->c_pos.y + y);
        clear_ring_pixel(ring->c_pos.x - x, ring->c_pos.y - y);
    }
    ring_draw_counter++;
}

void draw_ring_pixel(int8_t x, int8_t y, int every_nth){
    if (ring_draw_counter % every_nth == 0)
    {
        oled_write_pixel(x, y, true);
    }
    
    ring_draw_counter++;
}

void clear_ring_pixel(int8_t x, int8_t y){
    oled_write_pixel(x, y, false);
}

void solaris_init(uint32_t seed){
    if (initialized == 0){
        srand(seed);
        for (int16_t i = 0; i < MAX_PARTICLES; i++) {
            particles[i].pos = fvec2(10, 10);
            particles[i].c_pos = fvec2(20, 50);
            particles[i].radius = weighted_rand(20, 60, 0.1f);
            particles[i].orbitv = 50.f / particles[i].radius;
            particles[i].angle = (rand()%360) / 3.141592f;
        }
        small_ring.c_pos = ivec2(20, 50);
        small_ring.radius = 10;
        small_ring.n_th_pixel = 6;

        big_ring.c_pos = ivec2(20, 50);
        big_ring.radius = 30;
        big_ring.n_th_pixel = 9;

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

    clear_ring(&small_ring);
    draw_ring(&small_ring);

    clear_ring(&big_ring);
    draw_ring(&big_ring);
}

