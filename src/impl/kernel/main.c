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
    print_str("AceOS STARTED");
    print_char('\n');
    print_cursor();
    print_str("AceOS> ");
    while(1){
        Type();
    }
}