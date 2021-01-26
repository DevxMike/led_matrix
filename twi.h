#include <avr/io.h>
#include "data_structs.h"
#ifndef twi_h
#define twi_h

#define SLAVE 0xD0

uint8_t write_buff(uint8_t, uint8_t, uint8_t, const uint8_t*);
void read_buff(uint8_t, uint8_t, uint8_t, uint8_t*);

uint8_t init_RTC(void);
inline uint8_t bcd_to_dec(uint8_t bcd){
    return (bcd & 0x0F) + 10 * ((bcd >> 4) & 0x0F);
}
inline uint8_t dec_to_bcd(uint8_t dec){
    return ((dec/10) << 4) | (dec % 10);
}
uint8_t day_of_week(uint16_t y, uint8_t m, uint8_t d);
#endif