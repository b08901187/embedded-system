#include "teaadd.h"

PwmOut motor(D5);

void tea_add ()
{
        motor.period(0.02f);
        
        
        printf("start...\n");
        ThisThread::sleep_for(1000);
        
        for (int i=0; i<3; i++){
            motor.write(0.15f);
            ThisThread::sleep_for(1000);
            motor.write(0.05f);
            ThisThread::sleep_for(1000);
        }
        /*
        for (int i=0; i<3; i++){
            float k = 0.09;
            for (int j=0; j<12; j++){
                k += 1.0/200;
                motor.write(k);
                ThisThread::sleep_for(200);
            }
            for (int j=0; j<12; j++){
                k -= 1.0/200;
                motor.write(k);
                ThisThread::sleep_for(200);
            }
        }
        */
        printf("finish\n");
    
}




