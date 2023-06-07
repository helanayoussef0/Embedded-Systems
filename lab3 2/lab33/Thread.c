#include "LPC17xx.h"
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#define PI 3.14159265358979323846 /* pi */
#include <math.h>
#include <stdio.h>

//------- ITM Stimulus Port definitions for printf ------------------- //
//#define ITM_Port8(n) (*((volatile unsigned char *)(0xE0000000+4*n)))
//#define ITM_Port16(n) (*((volatile unsigned short*)(0xE0000000+4*n)))
//#define ITM_Port32(n) (*((volatile unsigned long *)(0xE0000000+4*n)))

//#define DEMCR (*((volatile unsigned long *)(0xE000EDFC)))
//#define TRCENA 0x0100000
/*----------------------------------------------------------------------------
 *      Sample threads
 *---------------------------------------------------------------------------*/
unsigned int counta=0;
unsigned int countb=0;
unsigned int countc=0;
  
void Thread1 (void const *argument); // thread function
void Thread2 (void const *argument); // thread function
void Thread3 (void const *argument); // thread function

//For Part 2
void ThreadA (void const *argument); // thread function 
void ThreadB (void const *argument); // thread function
void ThreadC (void const *argument); // thread function
void ThreadD (void const *argument); // thread function
void ThreadE (void const *argument); // thread function

osThreadId tid_Thread; // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread 1

osThreadId tid2_Thread; // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread 2

osThreadId tid3_Thread; // thread id
osThreadDef (Thread3, osPriorityNormal, 1, 0);  								 // thread 3


//Part 2 (priority based on Table I from the manual)
osThreadId tidA_Thread;
osThreadDef (ThreadA, osPriorityBelowNormal, 1, 0);

osThreadId tidB_Thread;
osThreadDef (ThreadB, osPriorityLow, 1, 0);

osThreadId tidC_Thread;
osThreadDef (ThreadC, osPriorityNormal, 1, 0);

osThreadId tidD_Thread;
osThreadDef (ThreadD, osPriorityBelowNormal, 1, 0);

osThreadId tidE_Thread;
osThreadDef (ThreadE, osPriorityLow, 1, 0);

int Init_Thread (void) {
	//creating threads
  tid_Thread = osThreadCreate (osThread(Thread1), NULL);
	tid2_Thread = osThreadCreate (osThread(Thread2), NULL);
	tid3_Thread = osThreadCreate (osThread(Thread3), NULL);
	
  if(!tid_Thread) return(-1);
  
  return(0);
}

int x=0;
int a=0;
int b=0;

void Thread3 (void const *argument) {		  // 3rd task
	for(countc=0;countc<=100000;countc++){ 	// a finite loop
			LPC_GPIO1->FIOPIN |= 1UL<<29; 				//initializing port1 pin 29
			LPC_GPIO1->FIOPIN &= ~(1UL<<29);				//clearing port1 pin 29
			a = countc/3;
			b = countc/6;
	}
	x = a*b;
	printf("Thread 3 is Done, the value calculated was %d\n",x);
}
void Thread2 (void const *argument) { 		//2nd task
	for(countb=0;countb<=100000;countb++){ 
			LPC_GPIO1->FIOPIN |= 1UL<<23; 				//initializing port1 pin 23
			LPC_GPIO1->FIOPIN &= ~(1UL<<23);				//clearing port1 pin 23
			a = countb/8;
			b = countb/4;
	}
	x = a*b;
	printf("Thread 2 is Done, the value calculated was %d\n",x);
}

void Thread1 (void const *argument) { 		//1st task
	 for(counta=0;counta<=100000;counta++){
		 	LPC_GPIO1->FIOPIN |= 1UL<<4; 				//initializing port1 pin 4
			LPC_GPIO1->FIOPIN &= ~(1UL<<4);				//clearing port1 pin 4
			a = counta/10;
			b = counta/5;
	}
	x =a*b;
	printf("Thread 1 is Done, the value calculated was %d\n",x);                                         
}

// Part 2
int Init_Part2 (void) {
	// the threads are created
	tidA_Thread = osThreadCreate (osThread(ThreadA), NULL);
	tidB_Thread = osThreadCreate (osThread(ThreadB), NULL);
	tidC_Thread = osThreadCreate (osThread(ThreadC), NULL);
	tidD_Thread = osThreadCreate (osThread(ThreadD), NULL);
	tidE_Thread = osThreadCreate (osThread(ThreadE), NULL);
	if(!tid_Thread) return(-1);
	return(0);
}

void ThreadA (void const *argument){
	int x;
	int A=0;
	for(x=0;x<=256;x++){
		A=A+x+(x+2);
	}
	printf("A: %d\n",A);
}

int temp;
int factorial(int a){
	temp = a--;
	while(a>1){
		temp *= a--;
	}
	return temp;
}

void ThreadB (void const *argument){
	double B=0;
	int n;
	for( n=1;n<=16;n++){
		B=B+((pow(2,(double)n))/factorial(n));
	}
	printf("B: %f\n",B);
}

void ThreadC (void const *argument){
	double C=0;
	int n;
	for(n=1;n<=16;n++){
		C=C+(((double)n+1)/n);
	}
	printf("C: %f\n",C);
}

void ThreadD (void const *argument){
	double D=1;
	int j;
	for(j = 1; j <= 5;j++){
		D=D+ ((pow(5,(double)j))/factorial(j));
	}
	printf("D: %f\n",D);
}

void ThreadE (void const *argument){
	double E=0;
	int n;
	int r =2;
	for(n=1;n<=12;n++){
		E=E+(PI*pow(r,2)*n);
	}
	printf("E: %f",E);
}