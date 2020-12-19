#include "spi.h"
void init_spi(void){
    DDRB |= (1 << PB5) | (1 << PB7) | (1 << PB4); //MOSI, SCK and !SS as outputs
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR1); //init spi, master mode, 64 prescaler
}
void send_byte(const uint8_t byte){
    SPDR = byte;
    while(!(SPSR & (1 << SPIF))) { continue; } //wait while transfer is not done
}
inline void set_ss(void){
    PORTB |= (1 << PB4);
}
inline void clr_ss(void){
    PORTB &= ~(1 << PB4);
}
void send_set(const reg_data_t* data){ //send 3 bytes set
    clr_ss();
    send_byte(data->third);
    send_byte(data->second);
    send_byte(data->first);
    set_ss();
}