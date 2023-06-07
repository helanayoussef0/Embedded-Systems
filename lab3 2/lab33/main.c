/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
 
extern int Init_Thread (void);
extern int Init_Part2 (void); 

/*
 * main: initialize and start the system
 */
int main (void) {
	//SystemInit();
  osKernelInitialize ();                    // initialize CMSIS-RTOS
 	Init_Thread ();														// Lab Assignment 1
	//Init_Part2();														// Lab Assignment 2
  osKernelStart ();                         // start thread execution 
	osDelay(osWaitForever);
}
