/*#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "frameBuffer.h"
#include "oled.h"
#include "images.h"

unsigned char *buffer;
int main()
{
    stdio_init_all();
    gpio_init(6);
    gpio_init(7);

    gpio_set_function(6, GPIO_FUNC_SPI);
    gpio_set_function(7, GPIO_FUNC_SPI);
    spi_init(spiPort, 1000000);
    buffer = malloc(buffer_size);
    FrameBuffer_clear(buffer);

    FrameBuffer_drawRect(buffer, 0, 0, 127, 63, true, draw);
    FrameBuffer_drawRect(buffer, 15, 15, 50, 20, true, draw);
    FrameBuffer_addBitmapImage(buffer, 50, 30, 16, 16, &hearthFrame1, invert);

    InitOled();
    sendBuffer(buffer);

    return 0;
}
*/