
#include "main.h"
#include "string.h"
#include "stdint.h"
#include <stdbool.h>

#define dcPin DC_Pin
#define resetPin RES_Pin
#define dcPinPort DC_GPIO_Port
#define resetPinPort RES_GPIO_Port
extern SPI_HandleTypeDef *spiPort;
#define width 128
#define height 64
#define PinOff(pinport, pin) HAL_GPIO_WritePin(pinport, pin, 0)
#define PinOn(pinport, pin) HAL_GPIO_WritePin(pinport, pin, 1)

void InitOled(SPI_HandleTypeDef *spiPort);
void sendBuffer(uint8_t *);
#define SSD1306_CONTRAST 0x81
#define SSD1306_DISPLAYALL_ON_RESUME 0xA4
#define SSD1306_DISPLAYALL_ON 0xA5
#define SSD1306_INVERTED_OFF 0xA6
#define SSD1306_INVERTED_ON 0xA7
#define SSD1306_DISPLAY_OFF 0xAE
#define SSD1306_DISPLAY_ON 0xAF
#define SSD1306_DISPLAYOFFSET 0xD3
#define SSD1306_COMPINS 0xDA
#define SSD1306_VCOMDETECT 0xDB
#define SSD1306_DISPLAYCLOCKDIV 0xD5
#define SSD1306_PRECHARGE 0xD9
#define SSD1306_MULTIPLEX 0xA8
#define SSD1306_LOWCOLUMN 0x00
#define SSD1306_HIGHCOLUMN 0x10
#define SSD1306_STARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_MEMORYMODE_HORZONTAL 0x00
#define SSD1306_MEMORYMODE_VERTICAL 0x01
#define SSD1306_MEMORYMODE_PAGE 0x10
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_COM_REMAP_OFF 0xC0
#define SSD1306_COM_REMAP_ON 0xC8
#define SSD1306_CLUMN_REMAP_OFF 0xA0
#define SSD1306_CLUMN_REMAP_ON 0xA1
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2
