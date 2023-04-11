#include "todo.h"
#include <string.h>

char buffer[256] = {'b','i','n','g'};


void todo_init(char* data, int buffer_size){
    memcpy(data, buffer, buffer_size);
}

void todo_handle_input(uint16_t keycode, keyrecord_t *record){

    if (record->event.pressed){
        buffer[0] = keycode;
    }
}

void todo_render(void){
    oled_write(buffer, false);
}

