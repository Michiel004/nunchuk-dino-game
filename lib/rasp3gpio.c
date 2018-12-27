#include "rasp3base.h"
#include "rasp3gpio.h"
#include <stdint.h>

//reference to the variable that holds all the registers
extern volatile unsigned int* REG;

//timer variable
volatile unsigned int tim;

void RP3_GPIO_set_function(uint8_t gpio, uint8_t function){
	uint8_t move = (gpio % 10) * 3;//what is the place of the needed bits
	switch(gpio / 10){//switch the needed registers
		//set the needed bits in the right register
		case 0: //0-9
			REG[GPFSEL0] = (REG[GPFSEL0] & ~(0b111 << move)) | (function << move);
			break;
		case 1: //10-19
			REG[GPFSEL1] = (REG[GPFSEL1] & ~(0b111 << move)) | (function << move);
			break;
		case 2: //20-29
			REG[GPFSEL2] = (REG[GPFSEL2] & ~(0b111 << move)) | (function << move);
			break;
		case 3: //30-39
			REG[GPFSEL3] = (REG[GPFSEL3] & ~(0b111 << move)) | (function << move);
			break;
		case 4: //40-49
			REG[GPFSEL4] = (REG[GPFSEL4] & ~(0b111 << move)) | (function << move);
			break;
		case 5: //40-49
			REG[GPFSEL5] = (REG[GPFSEL5] & ~(0b111 << move)) | (function << move);
			break;
	}
}

void RP3_GPIO_set_as_output(uint8_t gpio){
	RP3_GPIO_set_function(gpio, RP3_GPIO_function_output);
}

void RP3_GPIO_set_as_input(uint8_t gpio){
	RP3_GPIO_set_function(gpio, RP3_GPIO_function_input);
}

void RP3_GPIO_pin_set(uint8_t gpio){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//set the needed bits in the right register
		case 0:
			REG[GPSET0] = 1 << move;
			break;
		case 1:
			REG[GPSET1] = 1 << move;
			break;
	}
}

void RP3_GPIO_pin_clear(uint8_t gpio){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//set the needed bits in the right register
		case 0:
			REG[GPCLR0] = 1 << move;
			break;
		case 1:
			REG[GPCLR1] = 1 << move;
			break;
	}
}

uint8_t RP3_GPIO_pin_get(uint8_t gpio){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//get the needed bits from the right register
		case 0:
			return (REG[GPLEV0] >> move) & 1;
		case 1:
			return (REG[GPLEV1] >> move) & 1;
	}
}

void RP3_GPIO_pin_set_events(uint8_t gpio, uint8_t events){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//set the needed bits in the right register
		case 0:
			REG[GPREN0] = (REG[GPREN0] & ~(1 << move)) | ((events & 1) << move);
			REG[GPFEN0] = (REG[GPFEN0] & ~(1 << move)) | (((events >> 1) & 1) << move);
			REG[GPHEN0] = (REG[GPHEN0] & ~(1 << move)) | (((events >> 2) & 1) << move);
			REG[GPLEN0] = (REG[GPLEN0] & ~(1 << move)) | (((events >> 3) & 1) << move);
			REG[GPAREN0] = (REG[GPAREN0] & ~(1 << move)) | (((events >> 4) & 1) << move);
			REG[GPAFEN0] = (REG[GPAFEN0] & ~(1 << move)) | (((events >> 5) & 1) << move);
		case 1:
			REG[GPREN1] = (REG[GPREN1] & ~(1 << move)) | ((events & 1) << move);
			REG[GPFEN1] = (REG[GPFEN1] & ~(1 << move)) | (((events >> 1) & 1) << move);
			REG[GPHEN1] = (REG[GPHEN1] & ~(1 << move)) | (((events >> 2) & 1) << move);
			REG[GPLEN1] = (REG[GPLEN1] & ~(1 << move)) | (((events >> 3) & 1) << move);
			REG[GPAREN1] = (REG[GPAREN1] & ~(1 << move)) | (((events >> 4) & 1) << move);
			REG[GPAFEN1] = (REG[GPAFEN1] & ~(1 << move)) | (((events >> 5) & 1) << move);
	}
}

uint64_t RP3_GPIO_get_events(){
	//combine bolt registers and return them
	return REG[GPEDS0] | ((uint64_t)(REG[GPEDS1]) << 32);
}

uint8_t RP3_GPIO_get_event(uint8_t gpio){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//get the needed bits from the right register
		case 0:
			return (REG[GPEDS0] >> move) & 1;
		case 1:
			return (REG[GPEDS1] >> move) & 1;
	}
}

void RP3_GPIO_reset_events(){
	//clear bolt event registers
	REG[GPEDS0] = 0xffffffff;
	REG[GPEDS1] = 0xffffffff;
}

void RP3_GPIO_reset_event(uint8_t gpio){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	switch(gpio / 32){//switch the needed registers
		//set the needed bits in the right register
		case 0:
			REG[GPEDS0] = 1 << move;
			break;
		case 1:
			REG[GPEDS1] = 1 << move;
			break;
	}
}

void RP3_GPIO_set_pull(uint8_t gpio, RP3_GPIO_pull pull){
	uint8_t move = gpio % 32;//what is the place of the needed bits
	
	REG[GPPUD] = pull & 0x03;//set the needed pull
	for(tim = 0; tim < 150; tim++);//wait 150 cycles
	//set the needed register to 1
	if(gpio < 32)
		REG[GPPUDCLK0] = 1 << move;
	else
		REG[GPPUDCLK1] = 1 << move;
	for(tim = 0; tim < 150; tim++);//wait 150 cycles
	//set the needed register to 0
	if(gpio < 32)
		REG[GPPUDCLK0] = 0;
	else
		REG[GPPUDCLK1] = 0;
}

