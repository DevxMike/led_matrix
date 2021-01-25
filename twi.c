#include "twi.h"

void TWI_START(void){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA); //enable TWI, clear TWINT and START 
    while(!(TWCR & (1 << TWINT))) { 
        continue; 
    }
}
void TWI_STOP(void){
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); //clear TWINT, enable TWI and STOP
    while(!(TWCR & (1 << TWINT))) { 
        continue; 
    }
}
void TWI_WRITE(uint8_t byte){
    TWDR = byte; //place byte desired to send into reg
    TWCR = (1 << TWINT) | (1 << TWEN); //start transmission
}
uint8_t TWI_READ(uint8_t ack_bit){
    TWCR = (1 << TWINT) | (1 << TWEN) | (ack_bit << TWEA);
    while(!(TWCR & (1 << TWINT))) { 
        continue; 
    }
    return TWDR;
}
void write_buff(uint8_t slave, uint8_t ram_adr, uint8_t len, const uint8_t* buff){
    TWI_START();
    TWI_WRITE(slave);
    TWI_WRITE(ram_adr);
    while(len--){
        TWI_WRITE(*buff++);
    }
    TWI_STOP();
}
void read_buff(uint8_t slave, uint8_t ram_adr, uint8_t len, uint8_t* buff){
    TWI_START();
    TWI_WRITE(slave);
    TWI_WRITE(ram_adr);
    TWI_START();
    TWI_WRITE(slave + 1);
    while(len--){
        *buff++ = TWI_READ(len? 1 : 0);
    }
    TWI_STOP();
}