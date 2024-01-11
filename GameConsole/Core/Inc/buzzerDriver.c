/*
 * buzzerDriver.c
 *
 *  Created on: Feb 22, 2019
 *      Author: lukasz
 */
#include "main.h"
#include "buzzerDriver.h"
#include "melody.h"
#include "stdint.h"
#define CPU_FREQ 84000000
#define PRESCALER 84
long musicTimer = 0;
char changeNote = 1;
uint32_t currentFreq;
uint32_t currentDuration;
uint32_t durationTick;
char changedDurationTick = 0;
uint16_t currentSlowFactor;
uint8_t noteCounter = 0, partCounter = 0;

/*
 * 	Set new frequency
 *
 * 	args:
 * 	newFreq - new frequency in Hz.
 */
void buzzerSetNewFrequency(uint32_t newFreq)
{
	uint64_t tempFreq = newFreq;
	if (newFreq == 0)
		tempFreq = 999999;

	uint64_t tempNewValue = (uint64_t)CPU_FREQ / PRESCALER / tempFreq;

	// setting new value
	TIM1->ARR = (uint32_t)tempNewValue;
	TIM1->CCR3 = (uint32_t)tempNewValue / 2;
}

void musicHandler()
{

	if (changeNote)
	{

		changeNote = 0;

		currentFreq = melody[partCounter][noteCounter];
		currentDuration = noteDurations[partCounter][noteCounter];
		currentSlowFactor = melodySlowfactor[partCounter];
		changedDurationTick = 1;
		buzzerSetNewFrequency(currentFreq);
	}
	else
	{
		if (changedDurationTick == 1)
		{
			durationTick = uwTickFreq+ (currentDuration * currentSlowFactor);
			changedDurationTick = 0;
			musicTimer = HAL_GetTick();
		}
		if (HAL_GetTick() - musicTimer > durationTick){
			changeNote=1;
			noteCounter++;
			if(noteCounter>=melodySizes[partCounter]){
				noteCounter=0;
				partCounter++;
				if(partCounter==melodyCount){
					partCounter=0;
				}
			}
		}
	}
}
