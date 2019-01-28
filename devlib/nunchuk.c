#include <stdint.h>
#include "../lib/rasp3i2c.h"

void nunchuk_init()
{
	I2C_init();
	// initialize NUNCHUCK
	I2C_write(0x52,0x40,0x00); 
	I2C_write_without_regAddr(0x52, 0x00);  
}

short nunchuk_button_Z()
{
	short  reg5;
	short  Zbutton;
	I2C_write(0x52,0x05,0x00); 
	reg5 = I2C_Read();
	//When the button is pushed the value will be be zero.
	return Zbutton = reg5 & 0x01; // Return the first bit of reg 5.
}

short nunchuk_button_C()
{
	short  reg5;
	short  Cbutton;
	I2C_write(0x52,0x05,0x00); 
	reg5 = I2C_Read();
	//When the button is pushed the value will be be zero.
	return Cbutton = reg5 & 0x02; // Return the second bit of reg 5.
}

short nunchuk_xValue()
{
	short  reg0;
	I2C_write(0x52,0x00,0x00); 
	reg0 = I2C_Read();
	return reg0 ; // return the value of reg0 this is the xValue.
}

short nunchuk_yValue()
{
	I2C_write(0x52,0x01,0x00); 
	short reg1 = I2C_Read();
	return reg1 ; // return the value of reg1 this is the yValue.
}

short nunchuk_xAccell()
{
	I2C_write(0x52,0x02,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short xAccell =	(M <<2) | ((L & 0x0C) >> 2); // Combine the correct bits of reg2 and reg5. for the xAccell data. 
	return xAccell ; // Return the 10bit xAccell data. 
}

short nunchuk_yAccell()
{
	I2C_write(0x52,0x03,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short yAccell =	(M <<2) | ((L & 0x30) >> 4); // Combine the correct bits of reg3 and reg5. for the yAccell data. 
	return yAccell ; // Return the 10bit yAccell data. 
}

short nunchuk_zAccell()
{
	I2C_write(0x52,0x04,0x00); 
	short M = I2C_Read();
	I2C_write(0x52,0x05,0x00); 
	short L = I2C_Read();
	short zAccell =	(M <<2) | ((L & 0xC0) >> 6); // Combine the correct bits of reg4 and reg5. for the zAccell data. 
	return zAccell ; // Return the 10bit zAccell data.
}

