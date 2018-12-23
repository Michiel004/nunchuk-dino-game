#include "rasp3base.h"
#include "rasp3timer.h"
#include "rasp3int.h"

#include <stdint.h>

extern volatile unsigned int* REG;
void (*tickFunction)(void);

void timer_int();

void RP3_TIMER_init_tick(uint32_t us, void (*fun)()){
	REG[TIMCONT] = 0x00F90000;
	REG[TIMLOAD] = us - 1;
	REG[TIMREL]  = us - 1;
	REG[TIMPRED] = 0x000000F9;
	REG[TIMIRQC] = 0;
	REG[TIMCONT] = 0x003E00A2;
	tickFunction = fun;
	
	RP3_INT_enable_irq();
	RP3_INT_enableIRQFunction(IRQRQST_ATI, timer_int);
}

void timer_int(){
	REG[TIMIRQC] = 0;
	
	(*tickFunction)();
}