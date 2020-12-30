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
    {0x1F, 0x11, 0x11, 0x1F, 0x01, 0x01, 0x1F} //9
};
const uint8_t EEMEM set_quantity[16] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
};
const uint8_t EEMEM pwm_settings[] = {
    0, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105,
    110, 115, 120, 130, 140, 150, 170, 230, 255 
};

volatile uint8_t pwm = 255;
uint8_t active_cols;

void set_pwm(void){
    pwm = eeprom_read_byte(&pwm_settings[active_cols > 21? 21 : active_cols]);
}

uint8_t get_active_quantity(const reg_data_t* data){
    uint8_t sum = 0x00;
    sum += eeprom_read_byte(&set_quantity[data->first & 0x0F]);
    sum += eeprom_read_byte(&set_quantity[(data->first >> 4) & 0x0F]);
    sum += eeprom_read_byte(&set_quantity[data->second & 0x0F]);
    sum += eeprom_read_byte(&set_quantity[(data->second >> 4) & 0x0F]);
    sum += eeprom_read_byte(&set_quantity[data->third & 0x0F]);
    sum += eeprom_read_byte(&set_quantity[(data->third >> 4) & 0x0F]);

    return sum;
}
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
    active_cols = get_active_quantity(set);
    set_pwm();
}