#include "brush.h"

struct brush b;

volatile int32_t stroke_timer = 0;  
volatile int32_t lines_drawn = 0;

//uint8_t pre_brush_byte = 0x10;

//void pixel_toggle_func(uint8_t *data, void *user_args) {
    //uint8_t flake = *(uint8_t*)user_args;
    //pre_brush_byte = *data;
    //*data ^= flake;
//}

void brush_raise_hardness(void){
    b.hardness_base += 1;
}

void brush_lower_hardness(void){
    b.hardness_base -= 1;
}

void brush_init(void){
    b.pos = fvec2(0,0);
    b.vel = fvec2(0,0);
    b.hardness_base = 50;  
    b.hardness = 0;  
    b.size = ivec2(0, 0);
    b.stroke_len = 40;
    b.white = true;
    stroke_timer = 0;
    b.determ_pressure = rand()% 10;
}

void brush_animate(void){
    if (lines_drawn > MAX_LINES_TILL_RESET)
    {
        oled_clear();
        lines_drawn = 0;
    }
    
    b.pos.x += b.vel.x * DELTATIME;
    b.pos.y += b.vel.y * DELTATIME;
    int x = round_f(b.pos.x);
    int y = round_f(b.pos.y); 
    
    if (rand()%100 < DRAWCHANCE && stroke_timer <= 0)
    {
        //stroke_timer = (rand()%round_f(b.stroke_len / 3)) + (b.stroke_len * 3 / 4);
        stroke_timer = b.stroke_len; 
        bool start_from_top = rand()& 1;
        if (start_from_top){
            b.pos.x = rand()% BOX_WIDTH + BOX_TOP_LEFT_X;
            b.pos.y = BOX_TOP_LEFT_Y;
        }else{
            b.pos.x = BOX_TOP_LEFT_X;
            b.pos.y = rand()% BOX_HEIGHT + BOX_TOP_LEFT_Y;
        }
        
        int8_t vel = rand()% 4 + 8;
        b.vel.x = vel;
        b.vel.y = vel;
        //b.vel.x *= rand()& 1 ? -1 : 1;
        //b.vel.y *= rand()& 1 ? -1 : 1;
        b.size  = ivec2(rand()%6 + 1, rand()%6 + 1);
        b.pressure_delta = rand()% 8 - 4;
        b.determ_pressure = rand()% 10;
        b.determ.x = rand()% 1;
        b.determ.y = rand()% 1;
        b.hardness = rand()% 10 + b.hardness_base;
        b.white = !b.white;//rand() & 1;
        lines_drawn++;
    }
    if (stroke_timer > 0)
    {
        b.hardness += b.pressure_delta * (float) (rand()%10) * 0.1f;
        if (rand()%100 < b.determ.x)
        {
            b.vel.x *= (rand()%10 + 2) * 0.1f;
        }
        if (rand()%100 < b.determ.y)
        {
            b.vel.y *= (rand()%10 + 2) * 0.1f;
        }

        if (rand()%100 < b.determ_pressure)
        {
            b.pressure_delta = rand()% 8 - 4;
        }

        int16_t x_diff = x - BOX_TOP_LEFT_X;
        int16_t y_diff = y - BOX_TOP_LEFT_Y;

        if (x_diff >= 0 && x_diff + b.size.x <= BOX_WIDTH
         && y_diff >= 0 && y_diff + b.size.y <= BOX_HEIGHT)
        {
            ivec2_t c = ivec2(x+ b.size.x / 2, y+ b.size.y / 2);
            for (int32_t i = y; i <= y + b.size.y; i++)
            {
                for (int32_t j = x; j <= x + b.size.x; j++)
                {
                    int32_t dy = abs(c.y - i);
                    int32_t dx = abs(c.x - j);
                    //float dist = sqrt(dx * dx + dy * dy);
                    
                    if (rand()%100 < b.hardness - dy * 6 - dx * 6 - (abs(x_diff - BOX_WIDTH / 2)) -(abs(y_diff - BOX_HEIGHT / 2)))
                    {
                        //uint8_t line = round_f(i) / 8;
                        //uint8_t sub_pos = round_f(i) % 8;
                        //uint8_t brush_byte = 0b00000001 << sub_pos;
                        //oled_byte_apply_func(j, line, pixel_toggle_func, &brush_byte);
                        oled_write_pixel(j, i, b.white);
                    }
                }
            }
        } else
        {
            stroke_timer = 0;
        }
        
        stroke_timer--;
    }
}
    

