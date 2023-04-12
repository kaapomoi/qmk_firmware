#include "todo.h"
#include <string.h>

int cursor = 0;
char buffer[256] = {'b','i','n','g'};


void todo_init(char* data, int buffer_size){
    memcpy(data, buffer, buffer_size);
}

bool todo_handle_input(uint16_t keycode, keyrecord_t *record){
    bool needs_further_processing = false;
    if (keycode >= TC_A && keycode <= TC_Z){
        if (record->event.pressed) {
            buffer[cursor++] = keycode;
        }
    } else if (keycode == TC_BKSP){
        if (record->event.pressed) {
            buffer[cursor--] = 0;
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

