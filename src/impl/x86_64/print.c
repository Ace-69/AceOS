#include "print.h"

const static size_t NUM_COLS = 80; //MAI CAMBIARE STA MERDA QUA
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };

    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

size_t getrow(){
    return row;
}

size_t getcol(){
    return col;
}
void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
    row = 0, col = 0;
}

void print_newline() {
    col = 0;
    if (row < NUM_ROWS - 1) {
        row++;
        buffer[col + NUM_COLS * row] = (struct Char) {
            character: (uint8_t)((char)220),
            color: color,
        };
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            struct Char character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    clear_row(NUM_ROWS);
    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t)((char)220),
        color: color,
    };
}
void print_cursor(){
    buffer[col + NUM_COLS * row + 1] = (struct Char) {
        character: (uint8_t)((char)220),
        color: color,
    };
}
void printbackcurs(){
    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t)((char)220),
        color: color,
    };
}

void del_cursor(){
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };
    buffer[col + NUM_COLS * row] = empty;
    buffer[col + NUM_COLS * row + 1] = empty;
}

void deleteLastChar(){
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };
    buffer[col + NUM_COLS * row - 1] = empty;
    col--;
    print_cursor();
}

void print_char(char character) {
    if (character == '\n') {
        del_cursor();
        print_newline();
        return;
    }
    if (character == '\0') {
        return;
    }
    if (col > NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };
    print_cursor();
    col++;
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];

        if (character == '\0') {
            return;
        }

        print_char(character);
    }
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}

void print_error(char* str){
    uint8_t oldcolor = color;
    color = PRINT_COLOR_LIGHT_RED + (PRINT_COLOR_BLACK << 4);
    print_str(str);
    color = oldcolor;
}