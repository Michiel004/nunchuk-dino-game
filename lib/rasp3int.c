#include "rasp3int.h"
#include "rasp3base.h"

#include <stdint.h>

volatile unsigned int tim;

extern volatile unsigned int* REG;
extern void enable_irq_ASM ( void );

void (*IntterruptFunctions[16])(void);
uint16_t functionsUsed = 0;

int getIntterruptFunctionNumber(uint16_t reg);

void RP3_INT_enable_irq(){
	enable_irq_ASM();
}

void RP3_INT_enableIRQFunction(uint16_t reg, void (*fun)()){
	int ifn = getIntterruptFunctionNumber(reg);
	IntterruptFunctions[ifn] = fun;
	functionsUsed |= 1 <<ifn;
	if(reg < 64){
		if(reg < 32)
			REG[IRQENA1] = 1<<reg;
		else
			REG[IRQENA2] = 1<<(reg - 32);
	}
}

void RP3_INT_disableIRQFunction(uint16_t reg){
	int ifn = getIntterruptFunctionNumber(reg);
	functionsUsed &= ~(1 <<ifn);
	if(reg < 64){
		if(reg < 32)
			REG[IRQDIS1] = 1<<reg;
		else
			REG[IRQDIS2] = 1<<(reg - 32);
	}
}

void RASPBERRY_PI_INTERRUPT_SWI(){
	
}
	
void RASPBERRY_PI_INTERRUPT_PREFETCH(){
	
}

void RASPBERRY_PI_INTERRUPT_DATA(){
	
}

void RASPBERRY_PI_INTERRUPT_IRQ(){
	uint32_t intterupts1 = REG[IRQPEND1];
	uint32_t intterupts2 = REG[IRQPEND2];
	int i;
	for(i = 0; i < 32; i++){
		if((intterupts1 >> i) & 1){
			int ifn = getIntterruptFunctionNumber(i);
			if(ifn >= 0){
				if((functionsUsed >> ifn) & 1){
					(*IntterruptFunctions[ifn])(); 
				}
			}
		}
	}
	
	for(i = 0; i < 32; i++){
		if((intterupts2 >> i) & 1){
			int ifn = getIntterruptFunctionNumber(i+32);
			if(ifn >= 0){
				if((functionsUsed >> ifn) & 1){
					(*IntterruptFunctions[ifn])(); 
				}
			}
		}
	}
}

void RASPBERRY_PI_INTERRUPT_FIQ(){
	
}
	
int getIntterruptFunctionNumber(uint16_t reg){
	switch(reg){
		case IRQRQST_TIMERMATCH1:	return  0;
		case IRQRQST_TIMERMATCH3:	return  1;
		case IRQRQST_USBCONTROL:	return  2;
		case IRQRQST_AUX:			return  3;
		case IRQRQST_I2C_SPI_SLV:	return  4;
		case IRQRQST_PWA0:			return  5;
		case IRQRQST_PWA1:			return  6;
		case IRQRQST_SMI:			return  7;
		case IRQRQST_GPIO0:			return  8;
		case IRQRQST_GPIO1:			return  9;
		case IRQRQST_GPIO2:			return 10;
		case IRQRQST_GPIO3:			return 11;
		case IRQRQST_I2C:			return 12;
		case IRQRQST_SPI:			return 13;
		case IRQRQST_PCM:			return 14;
		case IRQRQST_UART:			return 15;
		default:					return -1;
	}
}