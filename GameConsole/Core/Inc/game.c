#include "game.h"

arrow *arrows[8] = {0};
int currentArrowNumber = 0;

unsigned char *HerathFrames[] = {hearthFrame1, hearthFrame2, hearthFrame3, hearthFrame4, hearthFrame5, hearthFrame6, hearthFrame7};

int Health = 7;
int score = 0;
int blockerState = 0; // where is blocker facing
unsigned char *GameBuffer;
unsigned int difficulty = 0; // will increase with score
unsigned int framecounter;
const unsigned int maxFrameForSpawn = 25;
bool isEnteredExitScreen = false;
void initGame(unsigned char *buffer)
{
    GameBuffer = buffer;
    enterScreen();
    spawnArrow(1, 0.5, false);
}

bool updateGame()
{
    framecounter++;
    if (framecounter > maxFrameForSpawn - difficulty)
    {
        spawnArrow(rand() % 4, 0.5 + (difficulty / 2), false);
        framecounter = 0;
    }

    if (Health >= 0)
    {

        FrameBuffer_clear(GameBuffer);
        updateBlocker();
        for (int i = 0; i < currentArrowNumber; i++)
        {
            if (arrows[i]->x > 0 && arrows[i]->x < 127 && arrows[i]->y > 0 && arrows[i]->y < 63)
            {
                FrameBuffer_addBitmapImage(GameBuffer, arrows[i]->x, arrows[i]->y, 16, 16, arrows[i]->image, draw);
            }
            updateArrow(arrows[i]);
            if (arrows[i]->isHit)
            {
                Health--;
            }
            if (arrows[i]->blocked)
            {
                score++;
            }
        }
        // sort arrows
        for (int i = 0; i < currentArrowNumber; i++)
        {
            if (arrows[i]->isHit || arrows[i]->blocked)
            {
                for (int j = i; j < currentArrowNumber; j++)
                {
                    arrows[j] = arrows[j + 1];
                }
                currentArrowNumber--;
            }
        }
        char point[3];
        sprintf(point, "%d", score);
        FrameBuffer_addBitmapImage(GameBuffer, 60, 29, 16, 16, HerathFrames[7 - Health], draw);
        FrameBuffer_drawText(GameBuffer, "Score:", 0, 0, true, draw, 1);
        FrameBuffer_drawText(GameBuffer, point, 35, 0, true, draw, 1);
        drawBlocker();
        difficulty = (int)(score / 7);
    }
    else
    {
        if (isEnteredExitScreen == false)
        {
            isEnteredExitScreen = true;
            exitScreen();
        }
    }
}
void enterScreen()
{
    bool outScreen = false;
    while (!outScreen)
    {
        FrameBuffer_clear(GameBuffer);

        FrameBuffer_drawText(GameBuffer, "Welcome to", 40, 0, true, draw, 1);
        FrameBuffer_drawText(GameBuffer, "the GAME", 40, 10, true, draw, 1);
        FrameBuffer_drawText(GameBuffer, "Press any", 40, 20, true, draw, 1);
        FrameBuffer_drawText(GameBuffer, "button to", 40, 30, true, draw, 1);
        FrameBuffer_drawText(GameBuffer, "start", 40, 40, true, draw, 1);

        if (HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin))
        {
            outScreen = true;
        }
        else if (HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin))
        {
            outScreen = true;
        }
        else if (HAL_GPIO_ReadPin(LEFT_GPIO_Port, LEFT_Pin))
        {
            outScreen = true;
        }
        else if (HAL_GPIO_ReadPin(RIGHT_GPIO_Port, RIGHT_Pin))
        {
            outScreen = true;
        }

        sendBuffer(GameBuffer);
    }
}
void exitScreen()
{
}

bool InBox(int x3, int y3, int x1, int y1, int x2, int y2)
{

    if (x1 > x2)
        x1, x2 = x2, x1;
    if (y1 > y2)
        y1, y2 = y2, y1;

    if ((x3 > x1) & (x3 < x2))
        if ((y3 > y1) & (y3 < y2))
            return true;
    return false;
}
void spawnArrow(int dir, float speed, bool isSpecial)
{
    arrow *arrw = malloc(sizeof(arrow));
    switch (dir)
    {
    case 0:
        arrw->image = arrowFrame1;
        arrw->x = 60, arrw->y = -16;
        arrw->topxOffset = 8, arrw->topyOffset = 8;
        arrw->blocked = false;
        arrw->isHit = false;
        break;
    case 1:
        arrw->image = arrowFrame2;
        arrw->x = 0, arrw->y = 28;
        arrw->topxOffset = 16, arrw->topyOffset = 8;
        arrw->blocked = false;
        arrw->isHit = false;
        break;
    case 2:
        arrw->image = arrowFrame3;
        arrw->x = 60, arrw->y = 64;
        arrw->topxOffset = 8, arrw->topyOffset = -1;
        arrw->blocked = false;
        arrw->isHit = false;
        break;
    case 3:
        arrw->image = arrowFrame4;
        arrw->x = 128, arrw->y = 28;
        arrw->topxOffset = -1, arrw->topyOffset = 8;
        arrw->blocked = false;
        arrw->isHit = false;
        break;
    }
    arrw->direction = dir;
    arrw->speed = 0.5;
    arrows[currentArrowNumber] = arrw;
    currentArrowNumber++;
}
void updateArrow(arrow *arrw)
{
    switch (arrw->direction)
    {
    case 0:
        arrw->y += arrw->speed;
        break;
    case 1:
        arrw->x += arrw->speed;
        break;
    case 2:
        arrw->y -= arrw->speed;
        break;
    case 3:
        arrw->x -= arrw->speed;
        break;
    }
    bool isBlocked = false;
    //FrameBuffer_drawRect(GameBuffer, 54, 24, 22, 28, true, draw);
    //FrameBuffer_drawRect(GameBuffer, arrw->x + arrw->topxOffset, arrw->y + arrw->topyOffset, 2, 2, true, draw);
    if (InBox(arrw->x + arrw->topxOffset, arrw->y + arrw->topyOffset, 60, 30, 74, 43)) // hearth hurtbox
    {
        arrw->isHit = true;
    }
    else if (InBox(arrw->x + arrw->topxOffset, arrw->y + arrw->topyOffset, 54, 24, 76, 52)) // blocker hitbox
    {
        isBlocked = true;
    }

    // check if the blocked facing the arrow
    switch (arrw->direction)
    {
    case 0:
        if ((blockerState == 0) & (isBlocked))
        {

            arrw->blocked = true;
        }
        break;
    case 1:
        if ((blockerState == 1) & (isBlocked))
        {

            arrw->blocked = true;
        }
        break;
    case 2:
        if ((blockerState == 2) & (isBlocked))
        {

            arrw->blocked = true;
        }
        break;
    case 3:
        if ((blockerState == 3) & (isBlocked))
        {

            arrw->blocked = true;
        }
        break;
    }
}

void drawBlocker()
{

    switch (blockerState)
    {
    case 0:
        FrameBuffer_addBitmapImage(GameBuffer, 55, 25, 24, 8, spearFrame1, draw);
        break;
    case 1:
        FrameBuffer_addBitmapImage(GameBuffer, 53, 25, 8, 24, spearFrame4, draw);
        break;
    case 2:
        FrameBuffer_addBitmapImage(GameBuffer, 55, 64 - 22, 24, 8, spearFrame3, draw);
        break;
    case 3:
        FrameBuffer_addBitmapImage(GameBuffer, 128 - 53, 25, 8, 24, spearFrame2, draw);
        break;
    default:
        FrameBuffer_addBitmapImage(GameBuffer, 55, 25, 24, 8, spearFrame1, draw);
        break;
    }
}

void updateBlocker()
{
    if (HAL_GPIO_ReadPin(UP_GPIO_Port, UP_Pin))
    {
        blockerState = 0;
    }
    else if (HAL_GPIO_ReadPin(DOWN_GPIO_Port, DOWN_Pin))
    {
        blockerState = 3;
    }
    else if (HAL_GPIO_ReadPin(LEFT_GPIO_Port, LEFT_Pin))
    {
        blockerState = 1;
    }
    else if (HAL_GPIO_ReadPin(RIGHT_GPIO_Port, RIGHT_Pin))
    {
        blockerState = 2;
    }
}
