/*
 * cv02.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Martin
 */

#include "main.h"
#include "cv.h"

#define PERIOD 300 //period in ms
#define BTN_PERIOD 40 //period in ms

void cv02_led()
{
	static uint32_t cTime;

	if (HAL_GetTick() > cTime + PERIOD)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		cTime = HAL_GetTick();
	}
}

void cv02_button()
{
	static uint32_t cTime;
	static uint32_t cTime2 = 0xFFFFFFFF;

	if (HAL_GetTick() > cTime + BTN_PERIOD)
	{
		if (!HAL_GPIO_ReadPin(S1_GPIO_Port, S1_Pin))
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, !GPIO_PIN_SET);
			cTime2 = HAL_GetTick();
		}
		cTime = HAL_GetTick();
	}

	if (HAL_GetTick() > cTime2 + 100)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, !GPIO_PIN_RESET);
		cTime2 = 0xFFFFFFFF;
	}

}
