#include "lib/rasp3gpio.h"
#include "lib/rasp3int.h"
#include "lib/rasp3spi.h"
#include "lib/rasp3i2c.h"
#include "lib/rasp3timer.h"

#include "devlib/libILIDraw.h"
#include "devlib/libILI9225.h"
#include "devlib/nunchuk.h"

#include "data/image_dino.h"
#include "data/image_ground.h"
#include "data/image_obst.h"

#include <stdint.h>

//volatile unsigned int tim;

int i = 0;
int j = 0;
int k = 0;

void tick();

uint32_t obstacles[] = {
	( 400 << 2) | 1,
	( 650 << 2) | 3,
	( 800 << 2) | 0,
	(1200 << 2) | 2,
	(1500 << 2) | 2,
	(2000 << 2) | 3,
	(2250 << 2) | 0,
	(2500 << 2) | 0,
	(2750 << 2) | 1,
	(3200 << 2) | 1,
	(3500 << 2) | 2,
	(4000 << 2) | 3,
	(4200 << 2) | 1,
	(4500 << 2) | 0,
	(4700 << 2) | 3,
	(4900 << 2) | 3
};

int y = 0;
int lasty = 0;
int dy = 0;
int death = 0;
short  Zbutton = 0;
short  Cbutton = 0;

int ticksToDo = 0;

int mainfunc(){
	
	I2C_init();
	nunchuk_init();
	
	LIB_ILIDRAW_init(40000000, 21, 8);
	
	LIB_ILI9225_set_display_mode(LIB_ILI9225_LCD_DISPLAY_MODE_0degrees_nflip, 0);
	LIB_ILIDRAW_clear(0x1f, 0x3f, 0x1f);
	
	RP3_TIMER_init_tick(200000, tick);
	ticksToDo = 0;
		
	i = 0;
	k = 0;
	y = 0;
	lasty = 0;
	dy = 0;
	death = 0;
	while(1){
		
		LIB_ILIDRAW_image_special(imageGround, i, 120, 600, 6);
		LIB_ILIDRAW_image_special(imageGround, i + 600, 120, 600, 6);
		
		//LIB_ILIDRAW_image_special_setMinMax(5, 100 - lasty, 22, 25);
		
		Zbutton = nunchuk_button_Z();
		Cbutton = nunchuk_button_C();
		
		
		if(death == 0){
			
			int k2 = 0;
			for(k2 = 0; k2 < NELEMS(obstacles); k2++){
				uint32_t o = obstacles[k2];
				int xCoord = -k + (o >> 2);
				LIB_ILIDRAW_image_special(imageObst[o & 3], xCoord, 100, 16, 26);
				
				//HIT DETECTION
				if(xCoord < 25 && (xCoord + 16) > 7){
					if (y < 24){
						death = 1;
					}
				}			
			}
			
			LIB_ILIDRAW_image_special_partial(imageDino[(j++) / 2 + 2], 5, 100 - y, 22, 25, 0, y, 22, 26 - y);
			if(lasty > y)
				LIB_ILIDRAW_clear_part(0xff, 0xff, 0xff, 5, 100 - lasty, 22, lasty - y);
			if(y > lasty)
				LIB_ILIDRAW_clear_part(0xff, 0xff, 0xff, 5, 100 - y + 25, 22, y - lasty);
			LIB_ILIDRAW_image_special_draw();
			LIB_ILIDRAW_image_partial(imageDino[(j++) / 2 + 2], 5, 100 - y, 22, 25, 0, 0, 22, y);
			
			i -= 12;
			k += 12;
			if(i <= -600)
				i = 0;
			if(j >= 4)
				j = 0;
			if(k > 5000)
				k = 0;
			
			if((Zbutton == 0) || (Cbutton == 0) ){
				if(y == 0 && dy == 0)
					dy = 8;
			}
			
			//JUMPING
			lasty = y;
			if( dy != 0 || y != 0){
				y = y + dy;
				dy = dy - 1;
				if(y <= 0){
					y = 0;
					dy = 0;
				}
			}
		}
		else
		{
			LIB_ILIDRAW_image_special(imageDino[4], 5, 100 - y, 22, 25);
			LIB_ILIDRAW_image_special_draw();
			if((Zbutton == 0) || (Cbutton == 0) ){
				death++;
				
			}
		}
		
		if(death >= 3){
			i = 0;
			k = 0;
			y = 0;
			lasty = 0;
			dy = 0;
			death = 0;
			LIB_ILIDRAW_clear(0x1f, 0x3f, 0x1f);
		}
				
		while(ticksToDo <= 0);
		ticksToDo--;
	}
	return 0;
}

void tick(){
	ticksToDo++;
}
