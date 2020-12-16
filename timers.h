#ifndef timers_h
#define timers_h
#include <avr/io.h>

void init_cycle_counter(void);
void init_mux_pwm(void);
inline void turn_pwm_on(void){
    TCCR2 |= (1 << CS20);
}
inline void turn_pwm_off(void){
    TCCR2 &= ~(1 << CS20);
}
#endif