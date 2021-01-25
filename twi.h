#include <avr/io.h>
#ifndef twi_h
#define twi_h
void write_buff(uint8_t, uint8_t, uint8_t, const uint8_t*);
void read_buff(uint8_t, uint8_t, uint8_t, uint8_t*);
#endif