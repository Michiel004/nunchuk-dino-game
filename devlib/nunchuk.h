#ifndef  NUNCHUK_H_
#define NUNCHUK_H_

#include "../lib/rasp3base.h"
#include <stdint.h>

void  nunchuk_init(); // initialize NUNCHUCK
short nunchuk_button_Z(); // Return the value of the Z button.
short nunchuk_button_C(); // Return the value of the C button.
short nunchuk_xValue();	// Return the x coördinaat of the NUNCHUCK.  
short nunchuk_yValue();	// Return the y coördinaat of the NUNCHUCK. 
short nunchuk_xAccell();// Return the x accelerometer data of the NUNCHUCK. 
short nunchuk_yAccell();// Return the y accelerometer data of the NUNCHUCK. 
short nunchuk_zAccell();// Return the z accelerometer data of the NUNCHUCK. 
#endif
