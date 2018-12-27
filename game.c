//#include "lib/rasp3gpio.h"
#include "lib/rasp3int.h"
//#include "lib/rasp3spi.h"
//#include "lib/rasp3i2c.h"
#include "lib/rasp3timer.h"

#include "devlib/libILIDraw.h"
#include "devlib/libILI9225.h"
#include "devlib/nunchuk.h"

#include "data/image_dino.h"
#include "data/image_ground.h"
#include "data/image_obst.h"

#include <stdint.h>

int 	groundAni 	= 0;
int 	dinoAni 	= 0;
int 	obstaAni 	= 0;
int 	death 		= 0;

int 	dinoY 		= 0;
int 	dinoLastY 	= 0;
int 	dinoDY 		= 0;

short  	Zbutton 	= 0;
short  	Cbutton 	= 0;

int 	ticksToDo 	= 0;

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

/* The function that handles the tick interrupt*/
void tick();

int mainfunc(){
	
	nunchuk_init(); //init nunchuk
	
	//init the screen and clear it
	LIB_ILIDRAW_init(40000000, 21, 8);
	LIB_ILI9225_set_display_mode(LIB_ILI9225_LCD_DISPLAY_MODE_0degrees_nflip, 0);
	LIB_ILIDRAW_clear(0x1f, 0x3f, 0x1f);
	
	RP3_TIMER_init_tick(200000, tick);//init the tick interrupt (200ms/tick)
	ticksToDo = 0;//tick still in queue
	
	//reset animations
	groundAni 	= 0;
	obstaAni 	= 0;
	dinoAni 	= 0;
	//reset dino position
	dinoY 		= 0;
	dinoLastY 	= 0;
	dinoDY 		= 0;
	death 		= 0;
	while(1){
		//draw the ground
		LIB_ILIDRAW_image_special(imageGround, groundAni, 120, 600, 6);
		LIB_ILIDRAW_image_special(imageGround, groundAni + 600, 120, 600, 6);

		//get the state of the nuchuck buttons
		Zbutton = nunchuk_button_Z();
		Cbutton = nunchuk_button_C();
		
		if(death == 0){ // if not death
			int k2 = 0;
			for(k2 = 0; k2 < NELEMS(obstacles); k2++){//go over each obstacle
				uint32_t o = obstacles[k2];
				//draw the obstacle
				int xCoord = -obstaAni + (o >> 2);
				LIB_ILIDRAW_image_special(imageObst[o & 3], xCoord, 100, 16, 26);
				
				//HIT DETECTION
				if(xCoord < 25 && (xCoord + 16) > 7){
					if (dinoY < 24){
						death = 1;//if hit, dino death
					}
				}			
			}
			//draw the part of the dino thats inside the special image
			LIB_ILIDRAW_image_special_partial(imageDino[(dinoAni) / 2 + 2], 5, 100 - dinoY, 22, 25, 0, dinoY, 22, 26 - dinoY);
			
			//clear the parts of the dino from last draw
			if(dinoLastY > dinoY)
				LIB_ILIDRAW_clear_part(0xff, 0xff, 0xff, 5, 100 - dinoLastY, 22, dinoLastY - dinoY);
			if(dinoY > dinoLastY)
				LIB_ILIDRAW_clear_part(0xff, 0xff, 0xff, 5, 100 - dinoY + 25, 22, dinoY - dinoLastY);
			
			LIB_ILIDRAW_image_special_draw(); // draw the special image
			//draw the rest of the dino
			LIB_ILIDRAW_image_partial(imageDino[(dinoAni) / 2 + 2], 5, 100 - dinoY, 22, 25, 0, 0, 22, dinoY);
			
			//calculate the next animations
			groundAni -= 12;
			obstaAni += 12;
			dinoAni++;
			if(groundAni <= -600)
				groundAni = 0;
			if(dinoAni >= 4)
				dinoAni = 0;
			if(obstaAni > 5000)
				obstaAni = 0;
			
			if((Zbutton == 0) || (Cbutton == 0) ){//do we want to jump
				if(dinoY == 0 && dinoDY == 0)//aren't we already jumping
					dinoDY = 8;//jump
			}
			
			//calculate the position and jumping parameters
			dinoLastY = dinoY;
			if( dinoDY != 0 || dinoY != 0){
				dinoY = dinoY + dinoDY;
				dinoDY = dinoDY - 1;
				if(dinoY <= 0){
					dinoY = 0;
					dinoDY = 0;
				}
			}
		}
		else //if death 
		{
			//draw death dino
			LIB_ILIDRAW_image_special(imageDino[4], 5, 100 - dinoY, 22, 25);
			LIB_ILIDRAW_image_special_draw();
			if((Zbutton == 0) || (Cbutton == 0)) death++;//count the button presses
		}
		
		if(death >= 3){//if the buttons are pressed a lot
			//reset the game
			groundAni = 0;
			obstaAni = 0;
			dinoY = 0;
			dinoLastY = 0;
			dinoDY = 0;
			death = 0;
			LIB_ILIDRAW_clear(0x1f, 0x3f, 0x1f);//clear the screen
		}
				
		while(ticksToDo <= 0);//wait for a tick in queue
		ticksToDo--;//remove tick from queue
	}
	return 0;
}

void tick(){//if timer ticked
	ticksToDo++;//add tick to queue
}
