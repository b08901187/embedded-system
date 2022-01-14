#include "heater.h"
#include "sound.h"
#include <cstdio>


PwmOut heater(D6);

#define OFF 0
#define ON 1

void turn_off_heater(){
    heater.period(1);
    heater.write(1);
}

void warm(float temp, float ref_temp)
{
    static int flag = OFF;
    static int warming = OFF;
    static float last_temp = temp;

    if (flag == OFF && warming == OFF){
        if (temp >= (ref_temp-20) * 0.1 + (ref_temp)){
            heater.write(1); 
        }
        else if (((temp < (ref_temp-20) * 0.1 + ref_temp)) && (temp > ref_temp)){
            heater.write(0);
            printf("warm\n");
            if(temp > last_temp) {warming = ON;} //溫度從下降改上升
        }
        else{
            heater.write(0);
            flag = ON;
            printf("heat\n");
        }
    }
    else if (flag == OFF && warming == ON) {
        if (temp >=ref_temp + 1 ){    
            heater.write(1);
        }
        else {
        heater.write(0);
        printf("warm\n");
        }
    }
    else{
        if (temp < ref_temp){
            heater.write(0);
            printf("heat\n");
        }
        else
            heater.write(1);
    }

    if(temp < float(ref_temp) + 1 && temp > float(ref_temp))
    {
        Cody();
    }

    last_temp = temp;
    
}