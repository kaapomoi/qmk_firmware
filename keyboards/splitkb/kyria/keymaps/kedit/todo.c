#include "todo.h"
#include <string.h>

#define MAX_BUFFER_SIZE 21*8

int g_cursor = 0;
char g_buffer[MAX_BUFFER_SIZE];

void todo_init(void) {
    //memset(g_buffer, '.', MAX_BUFFER_SIZE - 1);
}

int move_and_clamp_cursor(int cursor, int amount) {
    int moved_cursor = cursor + amount;
    return clamp_cursor(moved_cursor);
}

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

bool todo_handle_input(uint16_t keycode, keyrecord_t *record) {
    bool needs_further_processing = false;

    if (keycode == TC_COLN) {
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                g_buffer[g_cursor] = TC_SCOL;
            } else {
                g_buffer[g_cursor] = TC_COLN;
            }
            g_cursor = move_and_clamp_cursor(g_cursor, 1);
        }
    } else if (keycode == TC_BKSP){
        if (record->event.pressed) {
            g_cursor = move_and_clamp_cursor(g_cursor, -1);
            g_buffer[g_cursor] = 0;
            oled_clear();
        }
    } else if (keycode == TC_SPCE) {
        if (record->event.pressed) {
            g_buffer[g_cursor] = ' ';
            g_cursor = move_and_clamp_cursor(g_cursor, 1);
        }
    } else if (keycode == TC_LEFT) {
        if (record->event.pressed) {
            g_cursor = move_and_clamp_cursor(g_cursor, -1);
            oled_clear();
        }
    } else if (keycode == TC_DOWN) {
        if (record->event.pressed) {
            g_cursor = move_and_clamp_cursor(g_cursor, 21);
            oled_clear();
        }
    } else if (keycode == TC_UP) {
        if (record->event.pressed) {
            g_cursor = move_and_clamp_cursor(g_cursor, -21);
            oled_clear();
        }
    } else if (keycode == TC_RGHT) {
        if (record->event.pressed) {
            g_cursor = move_and_clamp_cursor(g_cursor, 1);
            oled_clear();
        }
    } else if (keycode >= TC_A && keycode <= TC_Z){
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                g_buffer[g_cursor] = keycode;
            } else {
                g_buffer[g_cursor] = keycode + 32;
            }
            g_cursor = move_and_clamp_cursor(g_cursor, 1);
        }
    } else if ((keycode >= TC_EXLM && keycode <= TC_AT) ||
               (keycode >= TC_OBRA && keycode <= TC_GRAV) ||
               (keycode >= TC_OBRE && keycode <= TC_TILD)) {
        if (record->event.pressed) {
            g_buffer[g_cursor] = keycode;
            g_cursor = move_and_clamp_cursor(g_cursor, 1);
        }
    } else {
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
    oled_write(g_buffer, false);
    render_cursor();
    oled_render();
}

