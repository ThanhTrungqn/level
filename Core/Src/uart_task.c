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

UART_HandleTypeDef huart7;
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
	Uart_data.Uart_cmd_duty= 10;
	Uart_data.Uart_cmd_freq= 25;
	Uart_data.Uart_cmd_lum = 50;
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
			uint8_t value = (Uart_data.Rx_Buffer[4] - '0')*10 + (Uart_data.Rx_Buffer[5] - '0');
			if ((value >=0) && (value <=50)){
				Uart_data.Uart_cmd_freq = value;
				Uart_data.Uart_cmd = UART_CMD_FREQ;
			}
			else{
				Uart_data.Uart_cmd = UART_CMD_FREQ_ERROR;
			}
		}
		//duty=xyz
		else if		((  Uart_data.Rx_Buffer[0]  == 'd')
					&& (Uart_data.Rx_Buffer[1]  == 'u')
					&& (Uart_data.Rx_Buffer[2]  == 't')
					&& (Uart_data.Rx_Buffer[3]  == 'y'))
		{
			uint8_t value =(Uart_data.Rx_Buffer[4] - '0')*10 + (Uart_data.Rx_Buffer[5] - '0');
			if ((value >=0) && (value <=50)){
				Uart_data.Uart_cmd_duty = value;
				Uart_data.Uart_cmd = UART_CMD_DUTY;
			}
			else{
				Uart_data.Uart_cmd = UART_CMD_DUTY_ERROR;
			}
		}
		//lum=xyz
		else if		((  Uart_data.Rx_Buffer[0]  == 'l')
					&& (Uart_data.Rx_Buffer[1]  == 'u')
					&& (Uart_data.Rx_Buffer[2]  == 'm'))
		{
			uint8_t value = 0;
			if (Uart_data.Rx_Buffer[6] ==  '\0'){
				if (Uart_data.Rx_Buffer[5] ==  '\0'){
					if (Uart_data.Rx_Buffer[4] ==  '\0'){
						if (Uart_data.Rx_Buffer[3] !=  '\0'){
							value = (Uart_data.Rx_Buffer[3] - '0');
						}
					}
					else
					{
						value = (Uart_data.Rx_Buffer[3] - '0')*10 + (Uart_data.Rx_Buffer[4] - '0');
					}
				}
				else
				{
					value = (Uart_data.Rx_Buffer[3] - '0')*100 + (Uart_data.Rx_Buffer[4] - '0')*10 + (Uart_data.Rx_Buffer[5] - '0');
				}
			}
			if ((value >=0) && (value <=100)){
				Uart_data.Uart_cmd_lum = value;
				Uart_data.Uart_cmd = UART_CMD_LUMINOSITY;
			}
			else{
				Uart_data.Uart_cmd = UART_CMD_LUMINOSITY_ERROR;
			}
		}
		else if		((  Uart_data.Rx_Buffer[0]  == 'l')
					&& (Uart_data.Rx_Buffer[1]  == 'e')
					&& (Uart_data.Rx_Buffer[2]  == 'x')
					&& (Uart_data.Rx_Buffer[3]  == 'i')
					&& (Uart_data.Rx_Buffer[4]  == 'l')
					&& (Uart_data.Rx_Buffer[5]  == 'i')
					&& (Uart_data.Rx_Buffer[6]  == 'g')
					&& (Uart_data.Rx_Buffer[7]  == 'h')
					&& (Uart_data.Rx_Buffer[8]  == 't'))
		{
			Uart_data.Uart_cmd = UART_CMD_LEXI_MODE;
		}
		else if		((  Uart_data.Rx_Buffer[0]  == 'n')
					&& (Uart_data.Rx_Buffer[1]  == 'o')
					&& (Uart_data.Rx_Buffer[2]  == 'r')
					&& (Uart_data.Rx_Buffer[3]  == 'm')
					&& (Uart_data.Rx_Buffer[4]  == 'a')
					&& (Uart_data.Rx_Buffer[5]  == 'l'))
		{
			Uart_data.Uart_cmd = UART_CMD_NORMAL_MODE;
		}
		else if		((  Uart_data.Rx_Buffer[0]  == 'o')
					&& (Uart_data.Rx_Buffer[1]  == 'n'))
		{
			Uart_data.Uart_cmd = UART_CMD_NORMAL_MODE;
		}
		else if		((  Uart_data.Rx_Buffer[0]  == 'o')
					&& (Uart_data.Rx_Buffer[1]  == 'f')
					&& (Uart_data.Rx_Buffer[2]  == 'f'))
		{
			Uart_data.Uart_cmd = UART_CMD_OFF_MODE;
		}
		else if		((  Uart_data.Rx_Buffer[0]  == 's')
					&& (Uart_data.Rx_Buffer[1]  == 't')
					&& (Uart_data.Rx_Buffer[2]  == 'a')
					&& (Uart_data.Rx_Buffer[3]  == 't')
					&& (Uart_data.Rx_Buffer[4]  == 'e'))
		{
			Uart_data.Uart_cmd = UART_CMD_STATE;
		}
		else{
			Uart_data.Uart_cmd = UART_CMD_ERROR;
			Uart_data.Uart_cmd_value = 0;
		}
		UART_Send_CMD();
		Uart_data.Transfer_cplt = false;
	}
}
void UART_Reset_CMD(){
	Uart_data.Uart_cmd = UART_WAIT_CMD;
	Uart_data.Uart_cmd_value = 0;
}
void UART_Send_CMD(){
	//uint8_t i = 0;
	uint8_t buffer[100];
	uint8_t len;
	switch (Uart_data.Uart_cmd)
	{
		case UART_CMD_FREQ:
			if (( Uart_data.Uart_cmd_freq>= 0 ) && ( Uart_data.Uart_cmd_freq <= 50)){
				uint8_t value = Uart_data.Uart_cmd_freq + 65;
				Lexi_Set_Freq(value);
				sprintf(buffer,"New Freq %i\r\n",Uart_data.Uart_cmd_freq);
				len=strlen(buffer);
				HAL_UART_Transmit(&huart7, buffer, len, 1000);
			}
			break;

		case UART_CMD_FREQ_ERROR:
			sprintf(buffer,"Freq must be 00 to 50\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_DUTY:
			if (( Uart_data.Uart_cmd_duty>= 0 ) && ( Uart_data.Uart_cmd_duty <= 50)){
				uint8_t value = Uart_data.Uart_cmd_duty + 10;
				Lexi_Set_Duty(value);
				sprintf(buffer,"New Duty %i \r\n",Uart_data.Uart_cmd_duty);
				len=strlen(buffer);
				HAL_UART_Transmit(&huart7, buffer, len, 1000);
			}
			break;

		case UART_CMD_DUTY_ERROR:
			sprintf(buffer,"Duty must be 00 to 50\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_LUMINOSITY:
			if ((Uart_data.Uart_cmd_lum <= 100)&& (Uart_data.Uart_cmd_lum >= 0)){
				Lexi_Set_Luminosity(Uart_data.Uart_cmd_lum);
				sprintf(buffer,"New Luminosity %i\r\n",Uart_data.Uart_cmd_lum);
				len=strlen(buffer);
				HAL_UART_Transmit(&huart7, buffer, len, 1000);
			}
			break;

		case UART_CMD_LUMINOSITY_ERROR:
			sprintf(buffer,"Luminosity must be 0, 1, 2 \r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_NORMAL_MODE:
			Lexi_Set_State_STANDARD();
			sprintf(buffer,"Light Mode Normal\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_LEXI_MODE:
			Lexi_Set_State_LEXI();
			sprintf(buffer,"Light Mode Lexi\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_OFF_MODE:
			Lexi_Set_State_OFF();
			sprintf(buffer,"Light Mode Off\r\n");
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 1000);
			break;

		case UART_CMD_STATE:
			sprintf(buffer,"-- State ");
			if ( Lexi_Get_Led_State() == 1){
				sprintf(buffer + strlen(buffer),"- LED NORMAL ");
				sprintf(buffer + strlen(buffer),"- Luminosity: %i ", Uart_data.Uart_cmd_lum);
			}
			else if ( Lexi_Get_Led_State() == 2){
				sprintf(buffer + strlen(buffer),"- LED LEXI MODE ");
				sprintf(buffer + strlen(buffer),"- Duty : %i " , Uart_data.Uart_cmd_duty );
				sprintf(buffer + strlen(buffer),"- Frequency : %i " , Uart_data.Uart_cmd_freq );
				sprintf(buffer + strlen(buffer),"- Luminosity : %i ", Uart_data.Uart_cmd_lum );
			}
			else if ( Lexi_Get_Led_State() == 0){
				sprintf(buffer + strlen(buffer),"- LED OFF ");
			}
			sprintf(buffer + strlen(buffer),"- Battery level: %i \r\n", BQ25713_Get_VBat());
			len=strlen(buffer);
			HAL_UART_Transmit(&huart7, buffer, len, 2000);
			break;

		default:
			break;
	}
}
