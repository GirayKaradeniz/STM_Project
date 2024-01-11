#include "oled.h"

bool inverted;
SPI_HandleTypeDef *spiPort;
void cmd(uint8_t cmd)
{
    PinOff(dcPinPort, dcPin);
    HAL_SPI_Transmit(spiPort, &cmd, 1, 100);
}
void InitOled(SPI_HandleTypeDef *spi)
{
    spiPort = spi;
    uint8_t setup[] = {
        SSD1306_DISPLAY_OFF,
        SSD1306_LOWCOLUMN,
        SSD1306_HIGHCOLUMN,
        SSD1306_STARTLINE,

        SSD1306_MEMORYMODE,
        SSD1306_MEMORYMODE_HORZONTAL,
        // flip the screen
        SSD1306_CLUMN_REMAP_ON,
        SSD1306_COM_REMAP_ON,
        //
        SSD1306_CONTRAST,
        0xFF,

        SSD1306_INVERTED_OFF,

        SSD1306_MULTIPLEX,
        63,

        SSD1306_DISPLAYOFFSET,
        0x00,

        SSD1306_DISPLAYCLOCKDIV,
        0x80,

        SSD1306_PRECHARGE,
        0x22,

        SSD1306_COMPINS,
        0x12,

        SSD1306_VCOMDETECT,
        0x40,

        SSD1306_CHARGEPUMP,
        0x14,

        SSD1306_DISPLAYALL_ON_RESUME,
        SSD1306_DISPLAY_ON};

    PinOn(resetPinPort, resetPin);
    HAL_Delay(5);
    PinOff(resetPinPort, resetPin);
    HAL_Delay(5);
    PinOn(resetPinPort, resetPin);
    PinOff(dcPinPort, dcPin);
    for (int i = 0; i < 27; i++)
    {
        cmd(setup[i]);
    }
}

void sendBuffer(uint8_t *buffer)
{
    PinOff(dcPinPort, dcPin);
    cmd(SSD1306_PAGEADDR); // Set page address from min to max
    cmd(0x00);
    cmd(0xff);
    cmd(SSD1306_COLUMNADDR); // Set column address from min to max
    cmd(0x00);
    cmd(127);

    // create a temporary buffer of size of buffer plus 1 byte for startline command aka 0x40
    unsigned char data[1];
    data[0] = SSD1306_STARTLINE;
    HAL_SPI_Transmit(spiPort, &data, 1, 100);
    PinOn(dcPinPort, dcPin);
    HAL_SPI_Transmit(spiPort, buffer, 1024, 100);
}
void setContrast(unsigned char contrast)
{
    cmd(SSD1306_CONTRAST);
    cmd(contrast);
}
void invertDisplay()
{
    cmd(SSD1306_INVERTED_OFF | !inverted);
    inverted = !inverted;
}
void setOrientation(bool orientation)
{
    // remap columns and rows scan direction, effectively flipping the image on display
    if (orientation)
    {
        cmd(SSD1306_CLUMN_REMAP_OFF);
        cmd(SSD1306_COM_REMAP_OFF);
    }
    else
    {
        cmd(SSD1306_CLUMN_REMAP_ON);
        cmd(SSD1306_COM_REMAP_ON);
    }
}