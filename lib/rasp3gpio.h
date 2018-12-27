#ifndef RASP3GPIO_H_
#define RASP3GPIO_H_

#include "rasp3base.h"
#include <stdint.h>

/**GPIO pull definition*/
typedef enum RP3_GPIO_pull { 
	RP3_GPIO_pull_non = 0,
	RP3_GPIO_pull_down = 1,
	RP3_GPIO_pull_up = 2
	} RP3_GPIO_pull;	

/**Set the function of the gpio pin.
   See the "RP3_GPIO_function_" defines.*/
void RP3_GPIO_set_function(uint8_t gpio, uint8_t function);

/**Set the gpio pin as output.*/
void RP3_GPIO_set_as_output(uint8_t gpio);

/**Set the gpio pin as input.*/
void RP3_GPIO_set_as_input(uint8_t gpio);

/**Set the output value of the gpio pin. (only works on output pins)*/
void RP3_GPIO_pin_set(uint8_t gpio);

/**Reset the output value of the gpio pin. (only works on ouput pins)*/
void RP3_GPIO_pin_clear(uint8_t gpio);

/**Get the value of the gpio pin. (only works on input pins)*/
uint8_t RP3_GPIO_pin_get(uint8_t gpio);

/**Turn on the specified event listeners on the gpio pin. (only works on input pins)
   See the "RP3_GPIO_event_" defines.*/
void RP3_GPIO_pin_set_events(uint8_t gpio, uint8_t events);

/**Get all the events in one variable, where each bit is a gpio pin.*/
uint64_t RP3_GPIO_get_events();

/**Get the event on a specified pin.*/
uint8_t RP3_GPIO_get_event(uint8_t gpio);

/**Reset all events.*/
void RP3_GPIO_reset_events();

/**Reset the specified event.*/
void RP3_GPIO_reset_event(uint8_t gpio);

/**Set the pull of a gpio pin.*/
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