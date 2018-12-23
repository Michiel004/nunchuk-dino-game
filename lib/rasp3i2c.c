#include "rasp3base.h"
#include "rasp3spi.h"
#include "rasp3gpio.h"
#include <stdint.h>

extern volatile unsigned int* REG;

int I2C_init()
{

	RP3_GPIO_set_function( 2, RP3_GPIO_function_af0);
	RP3_GPIO_set_function( 3, RP3_GPIO_function_af0);
	
	RP3_GPIO_set_pull( 2, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull( 3, RP3_GPIO_pull_non);

	REG[BSC1_DIV] = 2500;
}
// source : https://github.com/Pieter-Jan/PJ_RPI/blob/master/PJ_RPI.c
// Function to wait for the I2C transaction to complete

void wait_i2c_done() {
        //Wait till done, let's use a timeout just in case
        int timeout = 50;
        while((!((REG[BSC1_S]) & BSC_S_DONE))) {
        }
	REG[BSC1_S] = 0xff;
	volatile int i = 0;
	for(i=0 ; i < 250 ; i++);
}


int I2C_write(unsigned char slaveAddr,unsigned char regAddr, unsigned char regValue)
{
    REG[BSC1_A] = slaveAddr;

    REG[BSC1_DLEN] = 2;
    REG[BSC1_FIFO] = (unsigned char)regAddr;
    REG[BSC1_FIFO] = (unsigned char)regValue;
	
    REG[BSC1_S] = CLEAR_STATUS; 	// Reset status bits (see #define)
    REG[BSC1_C] = START_WRITE;    	// Start Write (see #define)

    wait_i2c_done();
}

int I2C_write_without_regAddr(unsigned char slaveAddr, unsigned char regValue)
{
    REG[BSC1_A] = slaveAddr;

    REG[BSC1_DLEN] = 1;
    REG[BSC1_FIFO] = (unsigned char)regValue;
	
    REG[BSC1_S] = CLEAR_STATUS; 	// Reset status bits (see #define)
    REG[BSC1_C] = START_WRITE;    	// Start Write (see #define)

    wait_i2c_done();
}

int I2C_Read()
{
    REG[BSC1_DLEN] = 1;

    REG[BSC1_S] = CLEAR_STATUS;	// Reset status bits (see #define)
    REG[BSC1_C] = START_READ;   // Start Read after clearing FIFO (see #define)

    wait_i2c_done();

    
    volatile int d = REG[BSC1_FIFO];	

    return d;
}
