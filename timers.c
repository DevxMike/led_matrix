#include "timers.h"
#include <avr/io.h>

void init_cycle_counter(void){
    TCCR1B |= (1 << CS11) | (1 << WGM12); //CTC mode, prescaler 8
    OCR1AH = 0x09;//2999 dec 
    OCR1AL = 0xC3;//interrupt every 1/800s 
    TIMSK |= (1 << OCIE1A);//enable interrupts
}