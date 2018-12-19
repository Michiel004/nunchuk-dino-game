#include "rasp3base.h"
#include "rasp3spi.h"
#include "rasp3gpio.h"
#include <stdint.h>

extern volatile unsigned int* REG;



void RP3_SPI_init(uint64_t clock){
	RP3_GPIO_set_function( 8, RP3_GPIO_function_af0);
	RP3_GPIO_set_function( 9, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(10, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(11, RP3_GPIO_function_af0);
	
	RP3_GPIO_set_pull( 8, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull( 9, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(10, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(11, RP3_GPIO_pull_non);
	
	REG[SPICLK] = (uint16_t)(250000000 / clock);
	//REG[SPICLK] = 0;
}


void RP3_SPI_transmit(char *t, int amount){
	REG[SPICS] = (1 << SPICS_TA);
	int sent = 0;
	int received = 0;
	
	while(sent < amount || received < amount){
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD))
				REG[SPIFIFO] = t[sent++];
		}
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD)){
				int temp = REG[SPIFIFO];
				received++;
			}
		}
	}
	REG[SPICS] &= ~(1 << SPICS_TA);
}

void RP3_SPI_receive(char *r, int amount){
	REG[SPICS] = (1 << SPICS_TA);
	int sent = 0;
	int received = 0;
	
	while(sent < amount || received < amount){
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD)){
				REG[SPIFIFO] = 0;
				sent++;
			}
		}
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD))
				r[received++] = REG[SPIFIFO];
		}
	}
	REG[SPICS] &= ~(1 << SPICS_TA);
}

void RP3_SPI_transcieve(char *t, char *r, int amount){
	REG[SPICS] = (1 << SPICS_TA);
	int sent = 0;
	int received = 0;
	
	while(sent < amount || received < amount){
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD))
				REG[SPIFIFO] = t[sent++];
		}
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD))
				r[received++] = REG[SPIFIFO];
		}
	}
	REG[SPICS] &= ~(1 << SPICS_TA);
}