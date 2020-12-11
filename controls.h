#ifndef controls_h
#define controls_h
#include <avr/io.h>

void controls_init(volatile uint8_t* dec_port, uint8_t dec, volatile uint8_t* inc_port, uint8_t inc);
void reg_pins(volatile uint8_t* dec_pin, volatile uint8_t* inc_pin);
extern uint8_t incK, decK;
void update_controls(void);
#endif