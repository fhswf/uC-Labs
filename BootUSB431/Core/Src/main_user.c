/*
 * main_user.c
 *
 *  Created on: Jun 10, 2024
 *      Author: tobi
 */


#include "main.h"
#include <stdio.h>
#include "usbd_cdc_if.h"
#include <string.h>


void main_user()
{
	char msg[]="Hello World\r\n";
	while(1)
	{
		CDC_Transmit_FS((unsigned char*)msg,strlen(msg));
		//printf("Hello Printf\r\n");
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_Delay(500);
	}
}
