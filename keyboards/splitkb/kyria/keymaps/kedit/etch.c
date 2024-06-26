#include "etch.h"

struct etch_cursor c;

void clamp(int16_t *v, int16_t min, int16_t max){
    if (*v < min)
    {
        *v = min;
        return;
    }
    if (*v > max)
    {
        *v = max;
        return;
    }
}

void etch_reset(void){
    oled_clear();
    etch_init();
}

void etch_move_cursor(enum dir d){
    switch (d)
    {
    case E_UP:
        c.pos.y--;
        break;
    case E_DOWN:
        c.pos.y++;
        break;
    case E_LEFT:
        c.pos.x--;
        break;
    case E_RIGHT:
        c.pos.x++;
        break;
    default:
        break;
    }
    clamp(&c.pos.x, MIN_X, MAX_X);
    clamp(&c.pos.y, MIN_Y, MAX_Y);
}

void etch_init(void){
    c.pos = ivec2(0, 0);
    c.white = true;
}
 
void etch_animate(void){
    oled_write_pixel(c.pos.x, c.pos.y, c.white);
}