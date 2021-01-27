#include "twi.h"

void TWI_START(void){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); //enable TWI, clear TWINT and START 
    while(!(TWCR & (1 << TWINT)));
}
void TWI_STOP(void){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); //clear TWINT, enable TWI and STOP
    return;
    while(!(TWCR & (1 << TWINT)));
}
void TWI_WRITE(uint8_t byte){
    TWDR = byte; //place byte desired to send into reg
    TWCR = (1 << TWINT) | (1 << TWEN); //start transmission
    while(!(TWCR & (1 << TWINT)));
}
uint8_t TWI_READ(uint8_t ack_bit){
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack_bit << TWEA);
    while(!(TWCR & (1 << TWINT)));
    return TWDR;
}
uint8_t write_buff(uint8_t slave, uint8_t ram_adr, uint8_t len, const uint8_t* buff){
    TWI_START();
    TWI_WRITE(slave);
    TWI_WRITE(ram_adr);
    while(len--){
        TWI_WRITE(*buff++);
    }
    TWI_STOP();
    return 0;
}
void read_buff(uint8_t slave, uint8_t ram_adr, uint8_t len, uint8_t* buff){
    TWI_START();
    TWI_WRITE(slave);
    TWI_WRITE(ram_adr);
    TWI_START();
    TWI_WRITE(slave + 1);
    while(len--){
        *buff++ = TWI_READ(len != 0? 1 : 0);
    }
    TWI_STOP();
}
uint8_t init_RTC(void){
    uint8_t buff[8] = { 0x00, 0x59, 0x00, 0x01, 0x25, 0x01, 0x21, 0x00 };
    write_buff(SLAVE, 0x00, 8, buff);
    return 0;
}
uint8_t day_of_week(uint16_t y, uint8_t m, uint8_t d){ 
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 
    if( m < 3 ) { 
        y -= 1; 
    } 
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
}