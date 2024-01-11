#include "frameBuffer.h"
#include "5x8_font.h"
const char width = 128, height = 64;
const unsigned char *font = font_5x8;
const int buffer_size = 1024;
void FrameBuffer_byteOR(unsigned char *buffer, int n, unsigned char byte)
{
    if (n > buffer_size - 1)
        return;
    buffer[n] |= byte;
}
void FrameBuffer_byteAND(unsigned char *buffer, int n, unsigned char byte)
{
    if (n > buffer_size - 1)
        return;
    buffer[n] &= byte;
}
void FrameBuffer_byteFLIP(unsigned char *buffer, int n, unsigned char byte)
{
    if (n > (buffer_size - 1))
        return;
    buffer[n] ^= byte;
}
void FrameBuffer_setPixel(unsigned char *buffer, int16_t x, int16_t y, bool color, Mode mode)
{
    if ((x < 0) || (x >= width) || (y < 0) || (y >= height))
        return;
    uint16_t byte = 0;
    byte = 1 << (y & 7);

    if ((int)mode == 1)
    {
        FrameBuffer_byteOR(buffer, x + ((y / 8) * width), byte);
    }
    else if ((int)mode == 0 || color == 0)
    {
        FrameBuffer_byteAND(buffer, x + ((y / 8) * width), ~byte);
    }
    else if ((int)mode == -1)
    {
        FrameBuffer_byteFLIP(buffer, x + ((y / 8) * width), byte);
    }
    else
    {
        FrameBuffer_byteOR(buffer, x + ((y / 8) * width), byte);
    }
}
void FrameBuffer_clear(unsigned char *buffer)
{
    memset(buffer, 0, buffer_size);
}
int FrameBuffer_getPixel(unsigned char *buffer, int x, int y)
{
    int value = 0;
    int index = 0;
    int bit = 0;
    if (x > width || y > height)
        value = -1;
    index = (y * width + x) / 8;
    bit = (y * width + x) % 8;
    value = (buffer[index] >> bit) & 1;
    return value;
}
void FrameBuffer_fill(unsigned char *buffer)
{
    memset(buffer, 255, buffer_size);
}
void FrameBuffer_addBitmapImage(unsigned char *buffer, int16_t anchorX, int16_t anchorY, uint16_t image_width, uint16_t image_height, uint8_t *image, Mode mode)
{
    uint8_t byte = 0;
    for (uint16_t y = 0; y < image_height; y++)
    {
        for (uint16_t x = 0; x < image_width / 8; x++)
        {
            byte = image[y * (image_width / 8) + x];

            for (uint16_t z = 0; z < 8; z++)
            {
                if ((byte >> (7 - z)) & 1)
                {
                    FrameBuffer_setPixel(buffer, x * 8 + z + anchorX, y + anchorY, 1, mode);
                }
            }
        }
    }
}

void FrameBuffer_drawRect(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool color, Mode mode)
{
    FrameBuffer_drawFastHLine(buffer, x, y, w, color, mode);
    FrameBuffer_drawFastHLine(buffer, x, y + h, w, color, mode);
    FrameBuffer_drawVerticalLine(buffer, x, y, h, color, mode);
    FrameBuffer_drawVerticalLine(buffer, x + w, y, h + 1, color, mode);
}
void FrameBuffer_drawLine(unsigned char *buffer, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, bool color, Mode mode)
{
    int x, y, dx, dy, dx0, dy0, px, py, xe, ye, i;
    dx = x1 - x0;
    dy = y1 - y0;
    dx0 = fabs(dx);
    dy0 = fabs(dy);
    px = 2 * dy0 - dx0;
    py = 2 * dx0 - dy0;
    if (dy0 <= dx0)
    {
        if (dx >= 0)
        {
            x = x0;
            y = y0;
            xe = x1;
        }
        else
        {
            x = x1;
            y = y1;
            xe = x0;
        }
        FrameBuffer_setPixel(buffer, x, y, color, mode);
        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
            {
                px = px + 2 * dy0;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y = y + 1;
                }
                else
                {
                    y = y - 1;
                }
                px = px + 2 * (dy0 - dx0);
            }
            FrameBuffer_setPixel(buffer, x, y, color, mode);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x0;
            y = y0;
            ye = y1;
        }
        else
        {
            x = x1;
            y = y1;
            ye = y0;
        }
        FrameBuffer_setPixel(buffer, x, y, color, mode);
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx0;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x = x + 1;
                }
                else
                {
                    x = x - 1;
                }
                py = py + 2 * (dx0 - dy0);
            }
            FrameBuffer_setPixel(buffer, x, y, color, mode);
        }
    }
}
void FrameBuffer_drawFastHLine(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t w, bool color, Mode mode)
{
    for (uint16_t i = 0; i < w; i++)
    {
        FrameBuffer_setPixel(buffer, x + i, y, color, mode);
    }
}
void FrameBuffer_drawVerticalLine(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t h, bool color, Mode mode)
{
    for (uint16_t i = y; i < (h + y); i++)
    {

        FrameBuffer_setPixel(buffer, x, i, color, mode);
    }
}
void FrameBuffer_fillRect(unsigned char *buffer, uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool color, Mode mode)
{

    for (uint16_t i = x; i < x + w; i++)
    {

        FrameBuffer_drawVerticalLine(buffer, i, y, h, color, mode);
    }
}
void FrameBuffer_drawChar(unsigned char *buffer, char c, uint16_t anchor_x, uint16_t anchor_y, bool color, Mode mode, uint16_t size)
{
    if (c < 32 || c > 126)
        return;

    uint16_t font_width = font_5x8[0];
    uint16_t font_height = font_5x8[1];

    uint16_t seek = (c - 32) * (font_width * font_height) / 8 + 2;

    uint16_t b_seek = 0;

    for (uint16_t x = 0; x < font_width; x++)
    {
        for (uint16_t y = 0; y < font_height; y++)
        {
            if (font_5x8[seek] >> b_seek & 0b00000001)
            {
                for (uint16_t i = 0; i < size; i++)
                {
                    for (uint16_t j = 0; j < size; j++)
                    {
                        FrameBuffer_setPixel(buffer, (x * size) + anchor_x, (y * size) + anchor_y, color, mode);
                    }
                }
            }
            b_seek++;
            if (b_seek == 8)
            {
                b_seek = 0;
                seek++;
            }
        }
    }
}
void FrameBuffer_drawText(unsigned char *buffer, const char *text, uint16_t anchor_x, uint16_t anchor_y, bool color, Mode mode, uint16_t size)
{
    uint16_t font_width = font_5x8[0];

    uint16_t n = 0;
    while (text[n] != '\0')
    {

        FrameBuffer_drawChar(buffer, text[n], anchor_x + (n * font_width * size), anchor_y, color, mode, size);

        n++;
    }
}