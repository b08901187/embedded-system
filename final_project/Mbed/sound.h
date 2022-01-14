/*
 * Copyright (c) 2014-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define Quarternote 300
#define Eighthnote Quarternote/2
#define Sixteenthnote Quarternote/4


void Radetzky_March();
void Cody();

// Adjust pin name to your board specification.
// You can use LED1/LED2/LED3/LED4 if any is connected to PWM capable pin,
// or use any PWM capable pin, and see generated signal on logical analyzer.

