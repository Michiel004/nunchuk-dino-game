#include "rasp3base.h"
#include "rasp3spi.h"
#include "rasp3gpio.h"
#include <stdint.h>

//reference to the variable that holds all the registers
extern volatile unsigned int* REG;

int I2C_init()
{

	RP3_GPIO_set_function( 2, RP3_GPIO_function_af0);	//SDA1
	RP3_GPIO_set_function( 3, RP3_GPIO_function_af0);	//SCL1


	// external pull-up resistor needed	
	RP3_GPIO_set_pull( 2, RP3_GPIO_pull_non);
	RP3_GPIO_set_pull( 3, RP3_GPIO_pull_non);

	REG[BSC1_DIV] = 2500; // communication speed 100 khz
}
// source : https://github.com/Pieter-Jan/PJ_RPI/blob/master/PJ_RPI.c
// Function to wait for the I2C transaction to complete

void wait_i2c_done() {
	
        while((!((REG[BSC1_S]) & BSC_S_DONE))) // waiting until FIFO is empty 
	{ 
        }
	REG[BSC1_S] = 0xff; // reset flag

	volatile int i = 0;
	for(i=0 ; i < 250 ; i++); // preventing race conditions
}


int I2C_write(unsigned char slaveAddr,unsigned char regAddr, unsigned char regValue)
{
    REG[BSC1_A] = slaveAddr;

    REG[BSC1_DLEN] = 2;
    REG[BSC1_FIFO] = (unsigned char)regAddr;
    REG[BSC1_FIFO] = (unsigned char)regValue;
	
    REG[BSC1_S] = CLEAR_STATUS; 	// Reset status bits
    REG[BSC1_C] = START_WRITE;    	// Start Write 

    wait_i2c_done();
}

int I2C_write_without_regAddr(unsigned char slaveAddr, unsigned char regValue)
{
    REG[BSC1_A] = slaveAddr;

    REG[BSC1_DLEN] = 1;
    REG[BSC1_FIFO] = (unsigned char)regValue;
	
    REG[BSC1_S] = CLEAR_STATUS; 	// Reset status bits
    REG[BSC1_C] = START_WRITE;    	// Start Write

    wait_i2c_done();
}

int I2C_Read()
{
    REG[BSC1_DLEN] = 1;

    REG[BSC1_S] = CLEAR_STATUS;	// Reset status bits
    REG[BSC1_C] = START_READ;   // Start Read after clearing FIFO

    wait_i2c_done();

 
    volatile int d = REG[BSC1_FIFO]; //  Read out FIFO value

    return d;
}
