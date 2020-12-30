#ifndef chars_h
#define chars_h

#include <avr/eeprom.h>
#include "spi.h"

enum dots_mode {
    none = 0, one, both
};

void prepare_set(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, reg_data_t*, uint8_t dots);
extern uint8_t active_cols;
#endif