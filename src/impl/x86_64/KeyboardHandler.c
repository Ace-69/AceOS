#include "KeyboardController.h"
#include "no.h"
#include "print.h"
#include "Commands.h"


#define PORT 0x60
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}
unsigned int restart_keyboard(){
    char data = inb(PORT);
    outb(PORT, data | 0x80);
    outb(PORT, data & 0x7f);
    return 0;
}
unsigned char getch() {
    char returnvalue = '\0';
    for(int i = 0; i < sizeof(layout_it); i++){
        if(inb(PORT) == layout_it[i]){
            returnvalue = corrispondente[i];
        }
    }
    return returnvalue;
}
char comando[72];
size_t contachar = 0, shift = 0, caps = 0;
void reset(){
    for(size_t i = 0; i < contachar; i++){
        //asm ("mov %0, 0" : "=a" (comando[i]));
        comando[i] = '\0';
    }
    contachar = 0;
}
void Type(){
    if(inb(0x64) & 0x1){
        //print_str(inb(PORT));
        if(getch() == 'E') {
            reset();
            del_cursor();
            print_newline();
            print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
            print_str(name);
            print_str("@AceOS>");
            print_set_color(PRINT_COLOR_LIGHT_GRAY, PRINT_COLOR_BLACK);
            print_char(' ');
        }
        if(getch() == 'L'|| getch() == 'R'){
            shift = 1;
        }
        if(inb(PORT) == 0xAA || inb(PORT) == 0xb6){
            shift = 0;
        }
        if(getch() == 'C'){
            if(caps == 0){
                caps = 1;
            } else {
                caps = 0;
            }
        }
        if(getch() == '\n'){
            if(comando[0] == '\0') return;
            del_cursor();
            Run(comando, contachar);
            reset();
            return;
        }
        if(getch() == 'B'){
            if(contachar > 0){
                deleteLastChar();
                del_cursor();
                comando[contachar] = '\0';
                contachar--;
                printbackcurs();
            }
            return;
        }
        if(getch() == ' ' && (contachar == 0 || comando[contachar-1] == ' ')){
            return;
        }
        if(getch() != '\0' && contachar != 71 && getch() != 'L' && getch() != 'R' && getch() != 'E' && getch() != 'C'){
            if(shift == 1 && caps == 0){
                print_char(toUpperCase(getch()));
                comando[contachar] = toUpperCase(getch());
            } else if(shift == 0 && caps == 1){
                print_char(toUpperCase(getch()));
                comando[contachar] = toUpperCase(getch());
            } else if(shift == 0 && caps == 0){
                print_char(getch());
                comando[contachar] = getch();
            } else if(shift == 1 && caps == 1){
                print_char(getch());
                comando[contachar] = getch();
            } else {
                print_char(getch());
                comando[contachar] = getch();
            }
            comando[contachar+1] = '\0';
            contachar++;
            return;
        }
    }
}
