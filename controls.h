#ifndef controls_h
#define controls_h
#include <avr/io.h>

void controls_init(volatile uint8_t* dec_port, uint8_t dec, volatile uint8_t* inc_port, uint8_t inc);
void reg_pins(volatile uint8_t* dec_pin, volatile uint8_t* inc_pin);
void function_init(volatile uint8_t* ok_port, uint8_t ok, volatile uint8_t* fn_port, uint8_t fn);
void reg_fn_pins(volatile uint8_t* ok_pin, volatile uint8_t* fn_pin);
extern uint8_t incK, decK, okK, functionK;
void update_controls(void);
#endif