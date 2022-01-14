#include "fan.h"


PwmOut fan(D3);


void rotation(float temp, float ref_temp)
{
    float PWM = sqrt(temp - ref_temp)/3;
    // specify period first
    if (PWM>0.4){
        fan.period(0.001f);  
        fan.write(PWM);      
        printf("fan: duty cycle = %f\n",PWM);   
    }
    else {
        fan.write(0);
    }
}