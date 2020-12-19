#ifndef spi_h
#define spi_h
#include <avr/io.h>
typedef struct{
    uint8_t first, second, third;
} reg_data_t;

void init_spi(void);
void send_set(const reg_data_t* data);
#endif