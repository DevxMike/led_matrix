#include "spi.h"
void send_byte(const uint8_t byte){
    SPDR = byte;
    while(!(SPSR & (1 << SPIF))) { continue; } //wait while transfer is not done
}
inline void set_ss(void){
    PORTB |= (1 << PB2);
}
inline void clr_ss(void){
    PORTB &= ~(1 << PB2);
}
void send_set(const reg_data_t* data){ //send 3 bytes set
    clr_ss();
    send_byte(data->third);
    send_byte(data->second);
    send_byte(data->first);
    set_ss();
}