#include "libILIDraw.h"
#include "libILI9225.h"

uint16_t savedIm[176][220];//the special image
//the draw position
int xMin = 177;
int yMin = 221;
int xMax = -1;
int yMax = -1;

//write a color to the screen
void LIB_ILIDRAW_write_color(uint8_t red, uint8_t green, uint8_t blue);
//set the position of the pointer
void LIB_ILIDRAW_set_position(uint16_t x, uint16_t y);

void LIB_ILIDRAW_init(uint32_t clock, int GPIO_RS, int GPIO_CS){
	LIB_ILI9225_init(clock, GPIO_RS, GPIO_CS);//init the screen
	
	//clear the special image
	int j = 0;
	int k = 0;
	for(j = 0; j <= 219; j++){
		for(k = 0; k <= 175; k++){
			savedIm[k][j] = 0xffff;
		}
	}
	//reset the draw position of the special image
	xMin = 221;
	yMin = 221;
	xMax = -1;
	yMax = -1;
}


void LIB_ILIDRAW_draw_pixel(uint16_t x, uint16_t y, uint16_t color){
	LIB_ILIDRAW_set_position(x, y);
	LIB_ILI9225_write_reg(LIB_ILI9225_WDGRAM	, color, 0xFFFF);
}

void LIB_ILIDRAW_image(uint16_t image[], int x, int y, int w, int h){
	//calculate the start and end positions
	int xs = x;
	int xe = x + w - 1;
	int ys = y;
	int ye = y + h - 1;
	
	//test if they are within the screen
	if(xs < 0) xs = 0;
	if(xe >= 175) xe = 175;
	if(ys < 0) ys = 0;
	if(ye >= 219) ye = 219;
	
	//set the window and position of the pointer
	LIB_ILI9225_set_window(xs, ys, xe, ye, 0);
	LIB_ILIDRAW_set_position(xs, ys);
	
	//start writing to the screen
	LIB_ILI9225_wcom(LIB_ILI9225_WDGRAM);
	
	//set every pixel of the image on the screen
	int j = 0;
	int k = 0;
	for(j = ys; j <= ye; j++){
		for(k = xs; k <= xe; k++){
			LIB_ILI9225_wdata(image[(j - y) * w + (k - x)]);
		}
	}
}

void LIB_ILIDRAW_image_partial(uint16_t image[], int x, int y, int w, int h, int startX, int startY, int width, int height){
	//check if the partial part is within the image
	if((startX + width) > w) width = w - startX;
	if((startY + height) > h) height = h - startY;
	if(width <= 0) return;
	if(height <= 0) return;
	
	//calculate the start and end positions
	int xs = x + startX;
	int xe = x + startX + width - 1;
	int ys = y + startY;
	int ye = y + startY + height - 1;
	
	//test if they are within the screen
	if(xs < 0) xs = 0;
	if(xe >= 175) xe = 175;
	if(ys < 0) ys = 0;
	if(ye >= 219) ye = 219;
	
	//set the window and position of the pointer
	LIB_ILI9225_set_window(xs, ys, xe, ye, 0);
	LIB_ILIDRAW_set_position(xs, ys);
	
	//start writing to the screen
	LIB_ILI9225_wcom(LIB_ILI9225_WDGRAM);
	
	//set every pixel wanted of the image on the screen
	int j = 0;
	int k = 0;
	for(j = ys; j <= ye; j++){
		for(k = xs; k <= xe; k++){
			LIB_ILI9225_wdata(image[(j - y) * w + (k - x)]);
		}
	}
}

void LIB_ILIDRAW_image_special(uint16_t image[], int x, int y, int w, int h){
	//calculate the start and end positions
	int xs = x;
	int xe = x + w - 1;
	int ys = y;
	int ye = y + h - 1;
	
	//test if they are within the screen
	if(xs < 0) xs = 0;
	if(xe >= 175) xe = 175;
	if(ys < 0) ys = 0;
	if(ye >= 219) ye = 219;
	
	//set the draw position of the special image
	if(xs < xMin) xMin = xs;
	if(ys < yMin) yMin = ys;
	if(xe > xMax) xMax = xe;
	if(ye > yMax) yMax = ye;
	
	//set every pixel of the image on the special image
	int j = 0;
	int k = 0;
	for(j = ys; j <= ye; j++){
		for(k = xs; k <= xe; k++){
			uint16_t pixel = image[(j - y) * w + (k - x)];
			if(pixel != 0xffff){
				savedIm[k][j] = pixel;
			}
		}
	}
}

void LIB_ILIDRAW_image_special_partial(uint16_t image[], int x, int y, int w, int h, int startX, int startY, int width, int height){
	if((startX + width) > w) width = w - startX;
	if((startY + height) > h) height = h - startY;
	if(width <= 0) return;
	if(height <= 0) return;
	
	//calculate the start and end positions
	int xs = x + startX;
	int xe = x + startX + width - 1;
	int ys = y + startY;
	int ye = y + startY + height - 1;
	
	//test if they are within the screen
	if(xs < 0) xs = 0;
	if(xe >= 175) xe = 175;
	if(ys < 0) ys = 0;
	if(ye >= 219) ye = 219;
	
	//set the draw position of the special image
	if(xs < xMin) xMin = xs;
	if(ys < yMin) yMin = ys;
	if(xe > xMax) xMax = xe;
	if(ye > yMax) yMax = ye;
	
	//set every pixel wanted of the image on the special image
	int j = 0;
	int k = 0;
	for(j = ys; j <= ye; j++){
		for(k = xs; k <= xe; k++){
			uint16_t pixel = image[(j - y) * w + (k - x)];
			if(pixel != 0xffff){
				savedIm[k][j] = pixel;
			}
		}
	}
}

void LIB_ILIDRAW_image_special_draw(){
	//set the window and position of the pointer
	LIB_ILI9225_set_window(xMin, yMin, xMax, yMax, 0);
	LIB_ILIDRAW_set_position(xMin, yMin);
	
	//start writing to the screen
	LIB_ILI9225_wcom(LIB_ILI9225_WDGRAM);
	
	int j = 0;
	int k = 0;
	
	for(j = yMin; j <= yMax; j++){
		for(k = xMin; k <= xMax; k++){
			LIB_ILI9225_wdata(savedIm[k][j]);
			savedIm[k][j] = 0xffff;
		}
	}
	xMin = 221;
	yMin = 221;
	xMax = -1;
	yMax = -1;
}

void LIB_ILIDRAW_image_special_setMinMax(int xs, int ys, int w, int h){
	int xe = xs + w - 1;
	int ye = ys + h - 1;
	
	//set the draw position of the special image
	if(xs < xMin) xMin = xs;
	if(ys < yMin) yMin = ys;
	if(xe > xMax) xMax = xe;
	if(ye > yMax) yMax = ye;
}

void LIB_ILIDRAW_clear(uint8_t red, uint8_t green, uint8_t blue){
	//set the start and end positions
	int xs = 0;
	int ys = 0;
	int xe = 219;
	int ye = 175;
	
	//set the window and position of the pointer
	LIB_ILI9225_set_window(ys, xs, ye, xe, 0);
	LIB_ILIDRAW_set_position(xs, ys);
	
	//start writing to the screen
	LIB_ILI9225_wcom(LIB_ILI9225_WDGRAM);
	
	//clear every pixel on the screen with the given color
	int j = 0;
	int k = 0;
	for(j = xs; j <= xe; j++){
		for(k = ys; k <= ye; k++){
			LIB_ILIDRAW_write_color(red, green, blue);
		}
	}
}

void LIB_ILIDRAW_clear_part(uint8_t red, uint8_t green, uint8_t blue, int x, int y, int w, int h){
	//calculate the start and end positions
	int xs = x;
	int xe = x + w - 1;
	int ys = y;
	int ye = y + h - 1;
	
	//test if they are within the screen
	if(xs < 0) xs = 0;
	if(xe >= 175) xe = 175;
	if(ys < 0) ys = 0;
	if(ye >= 219) ye = 219;
	
	//set the window and position of the pointer
	LIB_ILI9225_set_window(xs, ys, xe, ye, 0);
	LIB_ILIDRAW_set_position(xs, ys);
	
	//start writing to the screen
	LIB_ILI9225_wcom(LIB_ILI9225_WDGRAM);
	
	//clear every wanted pixel on the screen with the given color
	int j = 0;
	int k = 0;
	for(j = ys; j <= ye; j++){
		for(k = xs; k <= xe; k++){
			LIB_ILIDRAW_write_color(red, green, blue);
		}
	}
}

void LIB_ILIDRAW_write_color(uint8_t red, uint8_t green, uint8_t blue){
	uint16_t color = blue & 0x1F;
	color = color | ((green & 0x07) << 5);
	color = color | (((green >> 3) & 0x07) << 8);
	color = color | ((red & 0x1F) << 11);
	LIB_ILI9225_wdata(color);
}

void LIB_ILIDRAW_set_position(uint16_t x, uint16_t y){
	LIB_ILI9225_write_reg(LIB_ILI9225_RAMAS1	, x, 0xFFFF);
	LIB_ILI9225_write_reg(LIB_ILI9225_RAMAS2	, y, 0xFFFF);
}