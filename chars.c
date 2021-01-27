#include "chars.h"
const uint8_t EEMEM characters[][7] = {
    {0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F}, //0
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, //1
    {0x1F, 0x01, 0x01, 0x1F, 0x10, 0x10, 0x1F}, //2
    {0x1F, 0x01, 0x01, 0x1F, 0x01, 0x01, 0x1F}, //3
    {0x11, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x01}, //4
    {0x1F, 0x10, 0x10, 0x1F, 0x01, 0x01, 0x1F}, //5
    {0x1F, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x1F}, //6
    {0x1F, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}, //7
    {0x1F, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x1F}, //8
    {0x1F, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x1F}, //9
    {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, //A, 10
    {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E}, //B, 11
    {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E}, //D, 12
    {0x1F, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x1F}, //E, 13
    {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, //I, 14
    {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, //L, 15
    {0x11, 0x1B, 0x15, 0x11, 0x11, 0x11, 0x11}, //M, 16
    {0x11, 0x11, 0x19, 0x15, 0x13, 0x11, 0x11}, //N, 17
    {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11}, //R, 18
    {0x0E, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x0E}, //S, 19
    {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, //T, 20
    {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, //U, 21
    {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11}, //X, 22
    {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F}, //Z, 23
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F}, //_, 24
    {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11}, //H, 25
    {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, //O, 26
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //NULL 27
    {0x1F, 0x10, 0x10, 0x1F, 0x10, 0x10, 0x10} //F 28
};

void prepare_set(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth, uint8_t row, reg_data_t* set, uint8_t dots){
    first = eeprom_read_byte(&characters[first][row]); //read bytes from eemem defined by char codes
    second = eeprom_read_byte(&characters[second][row]);
    third = eeprom_read_byte(&characters[third][row]);
    fourth = eeprom_read_byte(&characters[fourth][row]);

    set->first = set->second = set->third = 0x00; //zero out data
    set->first |= (first << 3); //set first digit
    set->first |= (second & 0xF8) >> 3; //set 2 cols second digit
    set->second |= (second & 0x07) << 5; //set second digit
    set->second |= (third & 0xFE) >> 1; //4 rows third digit
    set->third |= (third & 0x01) << 7; //set third digit
    set->third |= fourth << 1;

    switch(dots){
        case one: if(row == 5) { set->second |= (1 << 4); } break;
        case both: if(row == 1 || row == 5) { set->second |= (1 << 4); } break;
        break;
    }
}