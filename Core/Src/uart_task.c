/*
 * bluetooth_task.c
 *
 *  Created on: Feb 10, 2020
 *      Author: tnguyen
 */

/* Includes ------------------------------------------------------------------*/
#include "uart_task.h"
#include <string.h>
#include "lexilight.h"

UART_HandleTypeDef huart5;
//Interrupt callback routine

//
/*

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == UART5)  //current UART
	{
		uint8_t i;
		if (Uart_data.Rx_indx == 0)  //clear Rx_Buffer before receiving new data
		{
			for (i=0 ; i<100 ; i++) {
				Uart_data.Rx_Buffer[i]=0;
			}
		}

		if ((Uart_data.Rx_data[0]!=10)&&(Uart_data.Rx_data[0]!=13)) //if received data different from ascii 13 (enter)
		{
			Uart_data.Rx_Buffer[Uart_data.Rx_indx]=Uart_data.Rx_data[0];    //add data to Rx_Buffer
			Uart_data.Rx_indx++;
		}
		else            //if received data = 13
		{
			Uart_data.Rx_indx=0;
			Uart_data.Transfer_cplt=true;//transfer complete, data is ready to read
			UART_Task();
		}
		HAL_UART_Receive_IT(&huart5, Uart_data.Rx_data, 1);   //activate UART receive interrupt every time
	}
}
*/
//UART MAIN TASK
void UART_Init(){
	//HAL_UART_Receive_IT(&huart5, Rx_data, 1);
	UART_Reset_CMD();
}

void UART_Task(){
	if (Uart_data.Transfer_cplt)
	{
		//Check data reveive here
		//freq=xyz
		if 	((  Uart_data.Rx_Buffer[0]  == 'f')
			&& (Uart_data.Rx_Buffer[1]  == 'r')
			&& (Uart_data.Rx_Buffer[2]  == 'e')
			&& (Uart_data.Rx_Buffer[3]  == 'q'))
		{
			Uart_data.Uart_cmd = UART_CMD_FREQ;
			Uart_data.Uart_cmd_value = (Uart_data.Rx_Buffer[5] - '0')*100 + (Uart_data.Rx_Buffer[6] - '0')*10 +  (Uart_data.Rx_Buffer[7] - '0');
			Lexi_Get_Duty();
		}
		//duty=xyz
		else if		((  Uart_data.Rx_Buffer[0]  == 'd')
					&& (Uart_data.Rx_Buffer[1]  == 'u')
					&& (Uart_data.Rx_Buffer[2]  == 't')
					&& (Uart_data.Rx_Buffer[3]  == 'y'))
		{
			Uart_data.Uart_cmd = UART_CMD_DUTY;
			Uart_data.Uart_cmd_value = (Uart_data.Rx_Buffer[5] - '0')*100 + (Uart_data.Rx_Buffer[6] - '0')*10 +  (Uart_data.Rx_Buffer[7] - '0');
		}
		//power=xyz
		else if		((  Uart_data.Rx_Buffer[0]  == 'p')
					&& (Uart_data.Rx_Buffer[1]  == 'o')
					&& (Uart_data.Rx_Buffer[2]  == 'w')
					&& (Uart_data.Rx_Buffer[3]  == 'e')
					&& (Uart_data.Rx_Buffer[4]  == 'r'))
		{
			Uart_data.Uart_cmd = UART_CMD_POWER;
			Uart_data.Uart_cmd_value = (Uart_data.Rx_Buffer[6] - '0')*100 + (Uart_data.Rx_Buffer[7] - '0')*10 +  (Uart_data.Rx_Buffer[8] - '0');
		}
		//lum=xyz
		else if		((  Uart_data.Rx_Buffer[0]  == 'l')
					&& (Uart_data.Rx_Buffer[1]  == 'u')
					&& (Uart_data.Rx_Buffer[2]  == 'm'))
		{
			Uart_data.Uart_cmd = UART_CMD_LUMINOSITY;
			Uart_data.Uart_cmd_value = (Uart_data.Rx_Buffer[4] - '0')*100 + (Uart_data.Rx_Buffer[5] - '0')*10 +  (Uart_data.Rx_Buffer[6] - '0');
		}
		else{
			Uart_data.Uart_cmd = UART_CMD_ERROR;
			Uart_data.Uart_cmd_value = 0;
		}
		UART_Send_CMD();
		//HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
		Uart_data.Transfer_cplt = false;
	}
}
void UART_Reset_CMD(){
	Uart_data.Uart_cmd = UART_CMD_ERROR;
	Uart_data.Uart_cmd_value = 0;
}
void UART_Send_CMD(){
	//uint8_t i = 0;
	uint8_t buffer[100];
	uint8_t len;
	switch (Uart_data.Uart_cmd)
	{
		case UART_CMD_FREQ:
			//sprintf(buffer,"This is i:%i\r\n",i);
			sprintf(buffer,"UART_CMD_FREQ\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart5, buffer, len, 1000);
			break;
		case UART_CMD_DUTY:
			//sprintf(buffer,"This is i:%i\r\n",i);
			sprintf(buffer,"UART_CMD_DUTY\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart5, buffer, len, 1000);
			break;
		case UART_CMD_POWER:
			//sprintf(buffer,"This is i:%i\r\n",i);
			sprintf(buffer,"UART_CMD_POWER\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart5, buffer, len, 1000);
			break;
		default:
			break;
	}
}
