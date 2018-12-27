#include "rasp3base.h"
#include "rasp3spi.h"
#include "rasp3gpio.h"
#include <stdint.h>

//reference to the variable that holds all the registers
extern volatile unsigned int* REG;

void RP3_SPI_init(uint64_t clock){
	//set the needed gpio pins to af0
	RP3_GPIO_set_function( 8, RP3_GPIO_function_af0);
	RP3_GPIO_set_function( 9, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(10, RP3_GPIO_function_af0);
	RP3_GPIO_set_function(11, RP3_GPIO_function_af0);
	
	//these pins also need to be not pulled
	RP3_GPIO_set_pull( 8, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull( 9, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(10, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull(11, RP3_GPIO_pull_non);
	
	//set the clock of the spi to the wanted clock
	REG[SPICLK] = (uint16_t)(250000000 / clock);
}

void RP3_SPI_transmit(char *t, int amount){
	//start transmission
	REG[SPICS] = (1 << SPICS_TA);
	
	int sent = 0;
	int received = 0;
	while(sent < amount || received < amount){
		//try to send until all is sent
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD))
				REG[SPIFIFO] = t[sent++];
		}
		
		//try to receive until all is received
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD)){
				int temp = REG[SPIFIFO];
				received++;
			}
		}
	}
	
	//stop transmission
	REG[SPICS] &= ~(1 << SPICS_TA);
}

void RP3_SPI_receive(char *r, int amount){
	//start transmission
	REG[SPICS] = (1 << SPICS_TA);
	
	int sent = 0;
	int received = 0;
	while(sent < amount || received < amount){
		//try to send 0 until the needed amount is sent
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD)){
				REG[SPIFIFO] = 0;
				sent++;
			}
		}
		
		//try to receive until all is received
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD))
				r[received++] = REG[SPIFIFO];
		}
	}
	
	//stop transmission
	REG[SPICS] &= ~(1 << SPICS_TA);
}

void RP3_SPI_transcieve(char *t, char *r, int amount){
	//start transmission
	REG[SPICS] = (1 << SPICS_TA);
	
	int sent = 0;
	int received = 0;
	while(sent < amount || received < amount){
		//try to send until all is sent
		if(sent < amount){
			if(REG[SPICS] & (1 << SPICS_TXD))
				REG[SPIFIFO] = t[sent++];
		}
		
		//try to receive until all is received
		if(received < amount){
			if(REG[SPICS] & (1 << SPICS_RXD))
				r[received++] = REG[SPIFIFO];
		}
	}
	
	//stop transmission
	REG[SPICS] &= ~(1 << SPICS_TA);
}