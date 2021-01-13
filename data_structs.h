#ifndef data_structs_h
#define data_structs_h
#include <avr/io.h>

typedef struct{
    uint8_t hours, mins;
}time_t;

typedef struct{
    uint8_t year, month, day_1, day_2; //day_1 - day of month, day_2 - day of week
}date_t;

typedef struct{
    date_t date;
    time_t time;
}time_data_t;

typedef struct{
    uint8_t days_flags : 7; //days of week when alm has to be triggered
    uint8_t other_flags : 2; //snoze, alm set
}flags_t;

typedef struct{
    time_t alm_time;
    flags_t flags;
    uint16_t tim;
    uint8_t state;
}alarm_t;

#endif