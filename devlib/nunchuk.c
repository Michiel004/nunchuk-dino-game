#include <stdint.h>
#include "../lib/rasp3i2c.h"

void nunchuk_init()
{
	I2C_init();
	I2C_write(0x52,0x40,0x00); // initialize NUNCHUCK
	I2C_write_without_regAddr(0x52, 0x00);  
}

short nunchuk_button_Z()
{
	short  reg5;
	short  Zbutton;
	I2C_write(0x52,0x05,0x00); 
	reg5 = I2C_Read();
	return Zbutton = reg5 & 0x01;
}

short nunchuk_button_C()
{
	short  reg5;
	short  Cbutton;
	I2C_write(0x52,0x05,0x00); 
	reg5 = I2C_Read();
	return Cbutton = reg5 & 0x02;
}

short nunchuk_xValue()
{
	short  reg0;
	I2C_write(0x52,0x00,0x00); 
	reg0 = I2C_Read();
	return reg0 ;
}

short nunchuk_yValue()
{
	I2C_write(0x52,0x01,0x00); 
	short reg1 = I2C_Read();
	return reg1 ;
}

short nunchuk_xAccell()
{
	I2C_write(0x52,0x02,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short xAccell =	(M <<2) | ((L & 0x0C) >> 2);
	return xAccell ;
}

short nunchuk_yAccell()
{
	I2C_write(0x52,0x03,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short yAccell =	(M <<2) | ((L & 0x30) >> 4);
	return yAccell ;
}

short nunchuk_zAccell()
{
	I2C_write(0x52,0x04,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short zAccell =	(M <<2) | ((L & 0xC0) >> 6);
	return zAccell ;
}

