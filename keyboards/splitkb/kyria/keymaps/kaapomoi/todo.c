#include "todo.h"
#include <string.h>

char buffer[128] = {'b','i','n','g'};


void todo_init(char* data, int buffer_size){
    memcpy(data, buffer, buffer_size);
}

void todo_handle_input(enum letter l){
    (void)l;
}

void todo_render(void){
    oled_write(buffer, false);
}

