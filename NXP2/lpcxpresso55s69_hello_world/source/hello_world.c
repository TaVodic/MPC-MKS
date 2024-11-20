/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "string.h"

#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_PORT BOARD_LED_BLUE_GPIO_PORT
#define BOARD_LED_PIN  BOARD_LED_BLUE_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
	if (g_systickCounter != 0U)
	{
		g_systickCounter--;
	}
}

void SysTick_DelayTicks(uint32_t n)
{
	g_systickCounter = n;
	while (g_systickCounter != 0U)
	{
	}
}

int constant_time_strcmp(const char *str1, const char *str2, size_t max_len) {
    uint8_t result = 0;

    for (size_t i = 0; i < max_len; i++) {
        // Pad the second string with '\0' if it's shorter than max_len
        uint8_t char1 = str1[i];
        uint8_t char2 = (i < max_len && str2[i] != '\0') ? str2[i] : '\0';

        result |= char1 ^ char2;
    }

    return result;
}
/*!
 * @brief Main function
 */
int main(void)
{
	GPIO_PortInit(GPIO, BOARD_LED_PORT);

	char ch;

	/* Init board hardware. */
	/* set BOD VBAT level to 1.65V */
	POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv,
	false);
	/* attach main clock divide to FLEXCOMM0 (debug console) */
	CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();

	LED_BLUE_INIT(1);

#if !defined(DONT_ENABLE_FLASH_PREFETCH)
	/* enable flash prefetch for better performance */
	SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif

	/* Set systick reload value to generate 1ms interrupt */
	if (SysTick_Config(SystemCoreClock / 1000U))
	{
		while (1)
		{
		}
	}

	PRINTF("hello world.\r\n");

	while (1)
	{
		/*SysTick_DelayTicks(1000U);

		 uint32_t DWT1, DWT2;
		 DWT1=DWT->CYCCNT;
		 LED_BLUE_TOGGLE();
		 DWT2=DWT->CYCCNT;
		 PRINTF("Cycles: %d\n", DWT2-DWT1);*/

		uint32_t DWT1, DWT2;
		uint8_t status = 0;

		char password_stored[20] = "1234";
		char input[20];

		PRINTF("\r\nEnter password: ");
		SCANF("%s", input);
		DWT1 = DWT->CYCCNT;
		status = constant_time_strcmp(input, password_stored, strlen(password_stored));
		DWT2 = DWT->CYCCNT;
		PRINTF("\r\nPassword: %s", input);
		if (status == 0)
		{
			PRINTF("\r\n Correct");
		}
		else
		{
			PRINTF("\r\n Incorrect");
		}
		PRINTF("\r\n Cycles: %d", DWT2 - DWT1);

	}
}
