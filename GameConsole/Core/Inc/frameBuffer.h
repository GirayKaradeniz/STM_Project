#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdbool.h>
#include <string.h>
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
    invert = -1,
    clear = 0,
    draw = 1,
    replace = 2,
    combine = 3,
    transparent = 4,

} Mode;

extern const char width, height;
extern const unsigned char *font;
extern const int buffer_size;
void FrameBuffer_byteOR(unsigned char *buffer, int n, unsigned char byte);
void FrameBuffer_byteAND(unsigned char *buffer, int n, unsigned char byte);
void FrameBuffer_byteFLIP(unsigned char *buffer, int n, unsigned char byte);
void FrameBuffer_setPixel(unsigned char *buffer, int16_t x, int16_t y, bool color, Mode mode);
void FrameBuffer_clear(unsigned char *buffer);
void FrameBuffer_fill(unsigned char *buffer);
int FrameBuffer_getPixel(unsigned char *buffer, int x, int y);
void FrameBuffer_addBitmapImage(unsigned char *buffer, int16_t anchorX, int16_t anchorY, uint16_t image_width, uint16_t image_height, uint8_t *image, Mode mode);
void FrameBuffer_drawChar(unsigned char *buffer, char c, uint16_t anchor_x, uint16_t anchor_y, bool color, Mode mode, uint16_t size);
void FrameBuffer_drawText(unsigned char *buffer, const char *text, uint16_t anchor_x, uint16_t anchor_y, bool color, Mode mode, uint16_t size);
void FrameBuffer_drawRect(unsigned char *buffer, uint16_t x_start, uint16_t y_start, uint16_t w, uint16_t h, bool color, Mode mode);
void FrameBuffer_drawLine(unsigned char *buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool color, Mode mode);
void FrameBuffer_drawFastHLine(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t w, bool color, Mode mode);
void FrameBuffer_drawVerticalLine(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t h, bool color, Mode mode);
void FrameBuffer_fillRect(unsigned char *buffer, uint16_t x_start, uint16_t y_start, uint16_t width, uint16_t height, bool color, Mode mode);

#endif