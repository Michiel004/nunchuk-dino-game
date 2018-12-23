#ifndef LIBILIDRAW_H_
#define LIBILIDRAW_H_

#include <stdint.h>

void LIB_ILIDRAW_init(uint32_t clock, int GPIO_RS, int GPIO_CS);
void LIB_ILIDRAW_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void LIB_ILIDRAW_image(uint16_t image[], int x, int y, int w, int h);
void LIB_ILIDRAW_image_partial(uint16_t image[], int x, int y, int w, int h, int startX, int startY, int width, int height);
void LIB_ILIDRAW_image_special(uint16_t image[], int x, int y, int w, int h);
void LIB_ILIDRAW_image_special_partial(uint16_t image[], int x, int y, int w, int h, int startX, int startY, int width, int height);
void LIB_ILIDRAW_image_special_draw();
void LIB_ILIDRAW_image_special_setMinMax(int xs, int ys, int xe, int ye);
void LIB_ILIDRAW_clear(uint8_t red, uint8_t green, uint8_t blue);
void LIB_ILIDRAW_clear_part(uint8_t red, uint8_t green, uint8_t blue, int x, int y, int w, int h);

#endif