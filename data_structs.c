#include "data_structs.h"

uint8_t flags;//first bit stands for alarm, second for buzzing while mins == secs == 00, third exit, fourth is set if buzzer enabled
    //fifth for check wheter data or time is being set

void check_alarm(alarm_t* alarms, const time_data_t* time, uint8_t quantity, const uint8_t coef){
    alarm_t* pt = alarms;
    uint8_t tmp = 0;

    

    for(uint8_t i = 0; i < quantity; ++i){
        switch(pt[i].state){
            case 1:
            tmp = (pt[i].alm_time.hours == time->time.hours) && (pt[i].alm_time.mins == time->time.mins) && (pt[i].flags.days_flags & (1 << time->date.day_2)) && !time->time.seconds;
            if((pt[i].flags.other_flags = tmp? 1 : 0)){
                if(!(flags & ALARM_MASK)) flags |= ALARM_MASK;
                pt[i].state = 2;
            } 
            break;
            
            case 2:
            if(!(flags & ALARM_MASK)) flags |= ALARM_MASK;
            if(okK){
                pt[i].tim = 60;
                pt[i].state = 3;
            }
            else if(incK){
                pt[i].tim = 60;
                pt[i].state = 5;
            }
            break;

            case 3:
            if(pt[i].tim && !okK){
                pt[i].state = 2;
            }
            else if(!pt[i].tim && okK){
                if(i >= 5){ //5 is a first non repetive alm
                    pt[i].flags.days_flags = 0;
                }
                pt[i].flags.other_flags = 0;
                pt[i].state = 4;
            }
            break;

            case 4:
            if(!okK){
                pt[i].state = 1;
            }
            break;

            case 5:
            if(pt[i].tim && !incK){
                pt[i].state = 2;
            }
            else if(!pt[i].tim && incK){
                pt[i].flags.other_flags = 2;
                pt[i].state = 6;
            }
            break;

            case 6:
            if(!incK){
                pt[i].tim = (uint32_t)coef * 2000 * 60; 
                pt[i].state = 7;
            }
            break;

            case 7:
            if(pt[i].tim == 0){
                pt[i].flags.other_flags = 1;
                pt[i].state = 2;
            }
            break;
        }
        if(pt[i].tim > 0) --pt[i].tim;
    }
    tmp = 0;
    for(uint8_t i = 0; i < quantity; ++i){
        if(pt[i].state == 2) ++tmp;
    }
    if(!tmp) flags &= ~ALARM_MASK;
    else if(tmp) if(!(flags & ALARM_MASK)) flags |= ALARM_MASK;
}

void init_alarms(alarm_t* alm, uint8_t q){
    for(uint8_t i = 0; i < q; ++i){
        alm[i].tim = alm[i].flags.other_flags = alm[i].flags.days_flags = 0;
        alm[i].state = 1;
        alm[i].alm_time.hours = alm[i].alm_time.mins = 0;
    }
}