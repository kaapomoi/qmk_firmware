#include "todo.h"
#include <string.h>

#define MAX_BUFFER_SIZE 256

int g_cursor = 0;
char g_buffer[MAX_BUFFER_SIZE] = {'b','i','n','g'};

int clamp_cursor(int c) {
    int max_cursor = MAX_BUFFER_SIZE;

    if (c <= 0) {
        c = 0;
    }
    if (c >= max_cursor) {
        c = max_cursor;
    }

    return c;
}

void todo_init(char* data, int buffer_size) {
    memcpy(data, g_buffer, buffer_size);
}

bool todo_handle_input(uint16_t keycode, keyrecord_t *record) {
    bool needs_further_processing = false;

    if (keycode >= TC_A && keycode <= TC_Z){
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                g_buffer[g_cursor] = keycode - 32;
            } else {
                g_buffer[g_cursor] = keycode;
            }
            g_cursor++;
            g_cursor = clamp_cursor(g_cursor);
        }
    } else if (keycode == TC_BKSP){
        if (record->event.pressed) {
            g_cursor--;
            g_cursor = clamp_cursor(g_cursor);
            g_buffer[g_cursor] = 0;
            oled_clear();
        }
    } else if (keycode == TC_SPAC) {
        if (record->event.pressed) {
            g_buffer[g_cursor] = ' ';
            g_cursor++;
            g_cursor = clamp_cursor(g_cursor);
        }
    }
    else { 
        needs_further_processing = true;
    } 

    return needs_further_processing;
}

void render_cursor(void) {
    int font_width = 6;
    int font_height = 8;
    int max_chars_w = 21;
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w), true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 1, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 2, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 3, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 4, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 5, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 6, true);
    oled_write_pixel(font_width*(g_cursor%max_chars_w), font_height*(g_cursor/max_chars_w) + 7, true);
}

void todo_render(void) {
    render_cursor();
    oled_write(g_buffer, false);
}

