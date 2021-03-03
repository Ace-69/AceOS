#include "MouseController.h"
#include "print.h"
#include "Commands.h"

#define PORT 0x60
#define MOUSE_STATUS 0x64
#define MOUSE_ABIT   0x02
#define MOUSE_BBIT   0x01
#define MOUSE_WRITE  0xD4
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08

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

uint8_t buffer[3], offset = 0, buttonsate = 0;


void mouse_wait(uint8_t a_type) {
	uint32_t timeout = 100000;
	if (!a_type) {
		while (--timeout) {
			if ((inb(MOUSE_STATUS) & MOUSE_BBIT) == 1) {
				return;
			}
		}
		return;
	} else {
		while (--timeout) {
			if (!((inb(MOUSE_STATUS) & MOUSE_ABIT))) {
				return;
			}
		}
		return;
	}
}

unsigned int restart_mouse(){
    char data = inb(MOUSE_WRITE);
    mouse_wait(0);
    outb(PORT, data | 0xf4);
    mouse_wait(0);
    outb(PORT, data & 0xf5);
    return 0;
}

void Mouse(){
    uint8_t stat = inb(0xF2);
    print_char((char)(stat-48));
    /*if(stat & MOUSE_BBIT){
        print_str("Mouse input: ");
        
        /*int8_t mouseInp = inb(PORT);
        if(stat & MOUSE_F_BIT){
            switch(offset){
                case 0:
                    buffer[0] = mouseInp;
                    if(!(mouseInp & MOUSE_V_BIT)) return; //is supposed to be always set. This helps to maintain and verify packet alignment.
                    offset++;
                    break;
                case 1:
                    buffer[1] = mouseInp;
                    offset++;
                    break;
                case 2:
                    buffer[2] = mouseInp;
                    if(buffer[0] & 0x80 || buffer[0] & 0x40) break; // buffer overflow

                    if(buffer[0] & 0x01) {
                        print_str("LClick");
                    }
                    if(buffer[0] & 0x02) {
                        print_str("RClick");
                    }
                    if(buffer[0] & 0x04) {
                        print_str("LClick");
                    }
                    offset = 0;
                    break;
            }
        }
    }*/
}