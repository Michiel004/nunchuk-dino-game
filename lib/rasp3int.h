#ifndef RASP3INT_H_
#define RASP3INT_H_

#include <stdint.h>

void RP3_INT_enable_irq();
void RP3_INT_enableIRQFunction(uint16_t reg, void (*fun)());
void RP3_INT_disableIRQFunction(uint16_t reg);

#endif