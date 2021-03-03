#include "print.h"
#include "KeyboardController.h"
#include "Commands.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

void kernel_main(){
    print_clear();
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    restart_keyboard();
    print_str("AceOS STARTED\n");
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_str("Inserire un nome da utilizzare in questa sessione.\nIl nome non potra' essere cambiato.\n");
    print_cursor();
    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("AceOS>");
    print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
    print_char(' ');
    while(1){
        Type();
    }
}