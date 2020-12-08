#include "timers.h"
#include <avr/io.h>

void init_cycle_counter(void){
    TCCR1B |= (1 << CS11) | (1 << WGM12); //CTC mode, prescaler 8
    OCR1AH = 0x13;//4999 dec 
    OCR1AL = 0x87;//interrupt every 1/400s 
    TIMSK |= (1 << OCIE1A);//enable interrupts
}