#ifndef timers_h
#define timers_h
#include <avr/io.h>

void init_timers(void);

inline void turn_pwm_on(void){
    TCCR2 |= (1 << CS20);
}
inline void turn_pwm_off(void){
    TCCR2 &= ~(1 << CS20);
}
#endif