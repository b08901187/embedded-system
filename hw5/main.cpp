/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "stm32l475e_iot01_accelero.h"
#include <cmath>

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.
PwmOut led(PWM_OUT);



int main()
{
    int16_t data[3] = {0};
    int16_t pre_data[3] = {0};
    double acc = 0;
    int max_acc = 10000;
    BSP_ACCELERO_Init();


    while (1){
        BSP_ACCELERO_AccGetXYZ(data);
        
        /*printf("\nACCELERO_X = %d\n", data[0]);
        printf("ACCELERO_Y = %d\n", data[1]);
        printf("ACCELERO_Z = %d\n", data[2]);*/

        
        acc = sqrt(pow(data[0]-pre_data[0], 2) + pow(data[1]-pre_data[1], 2) + pow(data[2]-pre_data[2], 2));
        
        printf("acceleration = %f\n", acc);


        ThisThread::sleep_for(100);
        
        pre_data[0] = data[0];
        pre_data[1] = data[1];
        pre_data[2] = data[2];
        
        // specify period first
        led.period(0.001f);      // 4 second period
        led.write(acc/max_acc);      // 50% duty cycle, relative to period
        //led = 0.5f;          // shorthand for led.write()
        //led.pulsewidth(2);   // alternative to led.write, set duty cycle time in seconds
    };
}
