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

void todo_render(void){
    oled_write(buffer, false);
}

