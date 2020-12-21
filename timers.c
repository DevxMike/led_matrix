#include "timers.h"


void init_cycle_counter(void){
    /*TCCR0 |= (1 << CS01) | (1 << CS00);
    TCNT0 = 255 - 124;
    TIMSK |= (1 << TOIE0);*/
    TCCR1B |= (1 << WGM12) | (1 << CS10); 
    OCR1AH = 0x1F;//1kHz
    OCR1AL = 0x3F;
    TIMSK |= (1 << OCIE1A);

    TCCR2 |= (1 << WGM21) | (1 << CS20); //CTC, no prescaler
    OCR2 = 30; //f ~= 1000*256 Hz 
    TIMSK |= (1 << OCIE2); //interrupt enable
}