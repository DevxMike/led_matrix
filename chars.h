#ifndef chars_h
#define chars_h

#include <avr/eeprom.h>
#include "spi.h"

void prepare_set(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, reg_data_t*);
#endif