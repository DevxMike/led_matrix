#include "timers.h"


void init_timers(void){
    TCCR1A = 0x00;
    TCCR1B = (1 << WGM12) | (1 << CS10); 
    OCR1AH = 0x1F;//2kHz
    OCR1AL = 0x3F;
    TIMSK |= (1 << OCIE1A);
}