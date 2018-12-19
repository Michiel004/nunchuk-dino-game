#ifndef RASP3GPIO_H_
#define RASP3GPIO_H_

#include "rasp3base.h"
#include <stdint.h>

typedef enum RP3_GPIO_pull { 
	RP3_GPIO_pull_non = 0,
	RP3_GPIO_pull_down = 1,
	RP3_GPIO_pull_up = 2
	} RP3_GPIO_pull;	

void RP3_GPIO_set_function(uint8_t gpio, uint8_t function);
void RP3_GPIO_set_as_output(uint8_t gpio);
void RP3_GPIO_set_as_input(uint8_t gpio);
void RP3_GPIO_pin_set(uint8_t gpio);
void RP3_GPIO_pin_clear(uint8_t gpio);
uint8_t RP3_GPIO_pin_get(uint8_t gpio);
void RP3_GPIO_pin_set_events(uint8_t gpio, uint8_t events);
uint32_t RP3_GPIO_get_event0();
uint32_t RP3_GPIO_get_event1();
void RP3_GPIO_reset_event0();
void RP3_GPIO_reset_event1();
void RP3_GPIO_set_pull(uint8_t gpio, RP3_GPIO_pull pull);

#define RP3_GPIO_function_input				0b000
#define RP3_GPIO_function_output			0b001
#define RP3_GPIO_function_af0				0b100
#define RP3_GPIO_function_af1				0b101
#define RP3_GPIO_function_af2				0b110
#define RP3_GPIO_function_af3				0b111
#define RP3_GPIO_function_af4				0b011
#define RP3_GPIO_function_af5				0b010

#define RP3_GPIO_event_rising_edge 			0
#define RP3_GPIO_event_falling_edge 		1
#define RP3_GPIO_event_high_detect 			2
#define RP3_GPIO_event_low_detect 			3
#define RP3_GPIO_event_async_rising_edge 	4
#define RP3_GPIO_event_async_falling_edge 	5

#endif