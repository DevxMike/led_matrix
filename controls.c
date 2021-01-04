#include "controls.h"

volatile uint8_t* _dec_pin, *_inc_pin, * _ok_pin, *_fn_pin; //thats temporary while working on prototype
uint8_t incK = 0, decK = 0, inc_offset, dec_offset;
uint8_t okK = 0, functionK = 0, ok_offset = 0, fn_offset = 0;
void controls_init(volatile uint8_t* dec_port, uint8_t dec, volatile uint8_t* inc_port, uint8_t inc){
    *dec_port |= (1 << dec); //pullups
    *inc_port |= (1 << inc);
    inc_offset = inc;
    dec_offset = dec;
}
void reg_pins(volatile uint8_t* dec_pin, volatile uint8_t* inc_pin){
    _dec_pin = dec_pin;
    _inc_pin = inc_pin;
}

void update_controls(void){
    incK = !((*_inc_pin) & (1 << inc_offset));
    decK = !((*_dec_pin) & (1 << dec_offset));
    okK = !((*_ok_pin) & (1 << ok_offset));
    functionK = !((*_fn_pin) & (1 << fn_offset));
}
void function_init(volatile uint8_t* ok_port, uint8_t ok, volatile uint8_t* fn_port, uint8_t fn){
    *ok_port |= (1 << ok);
    *fn_port |= (1 << fn);
    ok_offset = ok;
    fn_offset = fn;
}
void reg_fn_pins(volatile uint8_t* ok_pin, volatile uint8_t* fn_pin){
    _ok_pin = ok_pin;
    _fn_pin = fn_pin;
}