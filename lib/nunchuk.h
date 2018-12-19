#ifndef  NUNCHUK_H_
#define NUNCHUK_H_

#include "rasp3base.h"
#include <stdint.h>

void  nunchuk_init();
short nunchuk_button_Z();
short nunchuk_button_C();
short nunchuk_xValue();
short nunchuk_yValue();
short nunchuk_xAccell();
short nunchuk_yAccell();
short nunchuk_zAccell();
#endif
