#include "stdint.h"
#include "stdbool.h"

#include "images.h"
#include "frameBuffer.h"
#include "main.h"
typedef struct
{
    float x;
    float y;
    int topxOffset,topyOffset;
    int direction;
    float speed;
    bool isHit;
    bool blocked;
    unsigned char *image;
} arrow;
extern arrow *arrows[8];
extern int currentArrowNumber;
bool updateGame();
void initGame(unsigned char *buffer);
