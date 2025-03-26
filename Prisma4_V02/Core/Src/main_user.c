/************************************************************************************
 *
 *      oooooooooooooo          **
 *      o   .---.    o         ****   ***
 *      o   | * |   oo         ****   ***
 *       oo '---' oo           ****
 *         oo   oo              **           Fachhochschule Suedwestfalen
 *           ooo                **           Mechatronik / Mikrocomputer / EmbSys
 *            o                              (c) Prof. Tobias Ellermeyer
 *    ==================        **
 *     BALANCING PRISMA         **
 *
 *
 * main_user.c
 *
 *  Created on: Mar 25, 2025
 *      Author: tobi
 */


/***** TIMER Usage *****
 *
 *  TIM1  - Motor PWM
 *  TIM3  - Motor PWM
 *  TIM6  - Motor RPM calculation
 *  TIM7  - NeoPixel periodic update
 *  TIM8  - NeoPixel PWM/DMA LED
 *  TIM17 - 100Hz control loop (and optionally LED1 dimming)
 */

#include "main.h"
#include "uart.h"
#include "bluetooth.h"
#include <stdio.h>
#include "bldc.h"

#define MAIN_C
#include "globals.h"


void main_user(void)
{
	int cnt=0;
	HAL_Delay(200);
	uart_init();
	printf("UART Initialized\r\n");
	// Init Bluetooth
	bt_init();

	bldc_init();

	main_bmi();
	while(1)
	{

	}
}
