#ifndef data_structs_h
#define data_structs_h
#include <avr/io.h>

enum Month{
    january = 1, february, march, april, may, 
    june, july, august, september, october, november, december 
};

typedef struct{
    uint8_t hours : 5;
    uint8_t mins : 6;
    uint8_t seconds : 6; //seconds, max val 59 
}time_t;

typedef struct{
    uint8_t year : 7; //max val = 99
    uint8_t month : 4; //max val = 15
    uint8_t day_1 : 5; //max val = 31
    uint8_t day_2 : 3; //day_1 - day of month, day_2 - day of week
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
    uint32_t tim : 22; //max 7200000 -> 60 min
    uint8_t state;
}alarm_t;

#endif