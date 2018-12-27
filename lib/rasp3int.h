#ifndef RASP3INT_H_
#define RASP3INT_H_

#include <stdint.h>

/**Enable the interrupts.*/
void RP3_INT_enable_irq();

/**Enable an interrupt from its ID and run the given function when fired.*/
void RP3_INT_enableIRQFunction(uint16_t reg, void (*fun)());

/**Disable an interrupt from its ID.*/
void RP3_INT_disableIRQFunction(uint16_t reg);

#endif