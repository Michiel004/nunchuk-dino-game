#include "rasp3base.h"
#include "rasp3timer.h"
#include "rasp3int.h"

#include <stdint.h>

//reference to the variable that holds all the registers
extern volatile unsigned int* REG;

//the function to tick
void (*tickFunction)(void);

//timer interrupt
void timer_int();

void RP3_TIMER_init_tick(uint32_t us, void (*fun)()){
	//set the register for the timer
	REG[TIMCONT] = 0x00F90000;
	REG[TIMLOAD] = us - 1;
	REG[TIMREL]  = us - 1;
	REG[TIMPRED] = 0x000000F9;
	REG[TIMIRQC] = 0;
	REG[TIMCONT] = 0x003E00A2;
	
	//store the tick function
	tickFunction = fun;
	
	//enable the interrupts
	RP3_INT_enable_irq();
	RP3_INT_enableIRQFunction(IRQRQST_ATI, timer_int);
}

void timer_int(){
	REG[TIMIRQC] = 0;//the timer interrupt is handled
	(*tickFunction)(); //tick the tick function
}