/*
 * cv01.c
 *
 *  Created on: Jan 2, 2025
 *      Author: Martin
 */
#include "main.h"
#include "cv01.h"

void cv01()
{
	//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	/*GPIOC->BSRR |= (1 << 13);
	 HAL_Delay(1);
	 GPIOC->BRR |= (1 << 13);
	 HAL_Delay(1);*/
	//HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	//static uint8_t code[] = { 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0};
	static uint32_t code = 0b10101011001100110010101;

	/*for (uint8_t i = 0; i < sizeof(code); ++i)
	 {
	 HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, !code[i]);
	 HAL_Delay(100);
	 }

	 HAL_Delay(1000);*/

	for (uint8_t i = 0; i < 24; ++i)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, !((code >> i) & 1UL));
		HAL_Delay(100);
	}

	HAL_Delay(1000);
}

