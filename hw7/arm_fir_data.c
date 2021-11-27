/* ----------------------------------------------------------------------   
* Copyright (C) 2010-2012 ARM Limited. All rights reserved.   
*   
* $Date:        17. January 2013  
* $Revision: 	V1.4.0   
*   
* Project: 	    CMSIS DSP Library   
* Title:	     	arm_fir_data.c
*   
* Description:	 Data file used for example code
*   
* Target Processor: Cortex-M4/Cortex-M3/Cortex-M0
*  
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the 
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.  
 * -------------------------------------------------------------------- */

#include "arm_math.h"

/* ----------------------------------------------------------------------
** Test input signal contains 1000Hz + 15000 Hz
** ------------------------------------------------------------------- */

float32_t testInput_f32_1kHz_15kHz[30] =
{
 116.000000,213.000000,35.000000,-220.000000,-576.000000,-598.000000,-288.000000,-112.000000,
-78.000000,223.000000,236.000000,180.000000,111.000000,-89.000000,-289.000000,-425.000000,
-550.000000,-595.000000,-224.000000,74.000000,328.000000,695.000000,622.000000,647.000000,
545.000000,-41.000000,-561.000000,-560.000000,-168.000000,322.000000
};

float32_t refOutput[30] = 
{
    -0.211412672496714,	-0.572397214940051	,-0.402017263568073,	0.774316636371495,	3.12348857004136,	4.84350973843231,	
    2.76054049803466,	-4.96462814876364,	-16.0859763095671,	-22.8416812966443,	-13.0982800702242,	19.8583884534982,
    68.2233426202397,	107.284974363332,	103.861935401666,	34.4760109380496,	-96.9513095911916,	-253.944401746659,
    -380.256171158828,	-423.374227754788,	-360.054510883804,	-207.924820485017,	-17.1570914393736,	148.023973471112,	
    233.721452215061,	212.995623530223,	90.1718738504719,	-102.112710768223,	-310.600658000037,	-472.806916813052
};