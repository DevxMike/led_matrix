#include "timers.h"


void init_cycle_counter(void){
    TCCR0 |= (1 << WGM01) | (1 << CS01) | (1 << CS00); //CTC mode prescaler 64
    OCR0 = 249; //interrupt every 1/1000s (1kHz)
    TIMSK |= (1 << OCIE0);

    TCCR2 |= (1 << WGM21) | (1 << CS20); //CTC, no prescaler
    OCR2 = 62; //f ~= 1000*256 Hz 
    TIMSK |= (1 << OCIE2); //interrupt enable
}
void init_mux_pwm(void){ //OC0

}