#ifndef RASP3UART_H_
#define RASP3UART_H_

#include "rasp3base.h"
#include <stdint.h>

void RP3_TIMER_init_tick(uint32_t us, void (*fun)());

#endif