#include "button.h"
#include "teaadd.h"



/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

bool state = false;


Semaphore led_sem(0);


// This object drives both LD3 and LD4 on the board.
// Only one of these LEDs can be driven at a time.
InterruptIn button(BUTTON1);


double led_delay = 0.1; // 100 ms
volatile int button_switch = -1;


void button_pressed()
{
    if (button_switch == -1) {
    led_sem.release();
    }
}
void button_released()
{
    state = true;
}

bool button_check()
{

    button.fall(&button_pressed); // Change led delay
    button.rise(&button_released); // Change led
    if(state)
    {
        tea_add();
    }

    return state;
}