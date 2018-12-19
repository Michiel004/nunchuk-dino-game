#ifndef RASP3I2C_H_
#define RASP3I2C_H_

#include "rasp3base.h"
#include <stdint.h>

void i2c_init();
void wait_i2c_done();
void I2C_write(unsigned char slaveAddr,unsigned char regAddr, unsigned char regValue);
int I2C_write_without_regAddr(unsigned char slaveAddr, unsigned char regValue);
int I2C_Read();


#endif
