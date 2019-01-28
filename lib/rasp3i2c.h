#ifndef RASP3I2C_H_
#define RASP3I2C_H_

#include "rasp3base.h"
#include <stdint.h>

void I2C_init(); //Initialize the I2C ports and clock. 
void wait_i2c_done(); // wait until FIFO is empty or full depending on read or write function is used.
void I2C_write(unsigned char slaveAddr,unsigned char regAddr, unsigned char regValue);// write 2 bytes to slave
int I2C_write_without_regAddr(unsigned char slaveAddr, unsigned char regValue);// write 1 byte to slave
int I2C_Read(); //Receive the requested byte.


#endif
