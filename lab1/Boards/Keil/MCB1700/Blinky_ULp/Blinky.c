/*------------------------------------------------------------------------------
 * Copyright (c) 2004-2020 Arm Limited (or its affiliates). All
 * rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   1.Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   2.Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   3.Neither the name of Arm nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *------------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher for MCB1700
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "Blinky.h"
#include "LPC17xx.h"                    	// Device header
#include "Board_Joystick.h"								// Joystick controls


uint16_t ADC_last;                      	// Last converted value
static volatile uint8_t currentstate, updatedstate;
/*------------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) {
	Joystick_Initialize();										// Joystick Initialization
	LPC_SC->PCONP |= (1 << 15);								// GPIO power up
	currentstate = Joystick_GetState();
  printf("Joystick state is currently %d\n", currentstate);
	while (1) {                           	  // Loop forever
		updatedstate = Joystick_GetState();
		if(currentstate != updatedstate){
			switch(updatedstate){
				case JOYSTICK_CENTER:
					printf("Joystick is at the centre\n");					
					break;
				case JOYSTICK_DOWN:
					printf("Joystick is Down\n");
					break;
				case JOYSTICK_LEFT:
					printf("Joystick is Left\n");
					break;
				case JOYSTICK_RIGHT:
					printf("Joystick is Right\n");
					break;
				case JOYSTICK_UP:
					printf("Joystick is Up\n");
					break;
			}		
		currentstate = updatedstate;
		}
	}
}
