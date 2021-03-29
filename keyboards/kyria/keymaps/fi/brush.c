#include "brush.h"

struct brush b;

volatile int32_t stroke_timer = 0;  

//uint8_t pre_brush_byte = 0x10;

//void pixel_toggle_func(uint8_t *data, void *user_args) {
    //uint8_t flake = *(uint8_t*)user_args;
    //pre_brush_byte = *data;
    //*data ^= flake;
//}

void brush_init(void){
    b.pos = fvec2(0,0);
    b.vel = fvec2(1,1);
    b.hardness = 20;  
    b.size = ivec2(10,5);
    b.stroke_len = 30;
    b.white = true;
}

void brush_animate(void){
    b.pos.x += b.vel.x * DELTATIME;
    b.pos.y += b.vel.y * DELTATIME;
    int x = round_f(b.pos.x);
    int y = round_f(b.pos.y); 
    
    if (rand()%100 < DRAWCHANCE && stroke_timer <= 0)
    {
        stroke_timer = rand()%round_f(b.stroke_len / 3) + (b.stroke_len * 3 / 4);
        b.pos.x = rand()% MAX_X;
        b.pos.y = rand()% MAX_Y;
        b.vel.x = rand()% 12 - 6;
        b.vel.y = rand()% 12 - 6;
        b.pressure_delta = rand()% 4 - 2;
        b.determ.x = rand()% 10;
        b.determ.y = rand()% 5;
        b.hardness = 20;
        b.white = rand() & 1;
    }
    if (stroke_timer >= 0)
    {
        b.hardness += b.pressure_delta * (float) (rand()%10) * 0.1f;
        if (rand()%100 < b.determ.x)
        {
            b.vel.x += rand()%12 - 6;
        }
        if (rand()%100 < b.determ.y)
        {
            b.vel.y += rand()% 12 - 6;
        }

        if (x >= 0 && x + b.size.x <= MAX_X && y >= 0 && y + b.size.y <= MAX_Y)
        {
            ivec2_t c = ivec2(x+ b.size.x / 2, y+ b.size.y / 2);
            for (int32_t i = y; i <= y + b.size.y; i++)
            {
                for (int32_t j = x; j <= x + b.size.x; j++)
                {
                    int32_t dy = abs(c.y - i);
                    int32_t dx = abs(c.x - j);
                    //float dist = sqrt(dx * dx + dy * dy);
                    
                    if (rand()%100 < b.hardness - dy * 5 - dx * 5)
                    {
                        //uint8_t line = round_f(i) / 8;
                        //uint8_t sub_pos = round_f(i) % 8;
                        //uint8_t brush_byte = 0b00000001 << sub_pos;
                        //oled_byte_apply_func(j, line, pixel_toggle_func, &brush_byte);
                        oled_write_pixel(j, i, b.white);
                    }
                }
            }
        }else
        {
            stroke_timer = 0;
        }
        
        stroke_timer--;
    }
}
    

