/*
 * bluetooth_task.h
 *
 *  Created on: Feb 10, 2020
 *      Author: tnguyen
 */

#ifndef BLUETOOTH_TASK_H_
#define BLUETOOTH_TASK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
	/* Uart commande */
	UART_CMD_FREQ =0,				//Change FREQ
	UART_CMD_FREQ_ERROR,			//FREQ ERROR
	UART_CMD_DUTY,					//Change DUTY
	UART_CMD_DUTY_ERROR,			//DUTY ERROR
	UART_CMD_LUMINOSITY,			//Change LUMINOSITY
	UART_CMD_LUMINOSITY_ERROR,		//LUMINOSITY ERROR
	UART_CMD_LEXI_MODE,				//LEXI MODE
	UART_CMD_NORMAL_MODE,			//NORMAL MODE
	UART_CMD_OFF_MODE,				//OFF MODE
	UART_CMD_SCREEN,				//Change SCREEN
	UART_CMD_STATE,
	UART_WAIT_CMD,
	UART_CMD_ERROR			//Error
} UART_CMD;

typedef struct {
	uint8_t 	Rx_indx;
	uint8_t 	Rx_data[2];
	uint8_t 	Rx_Buffer[100];
	bool 		Transfer_cplt;
	UART_CMD 	Uart_cmd;
	uint8_t		Uart_cmd_value;
	uint8_t		Uart_cmd_duty;
	uint8_t		Uart_cmd_freq;
	uint8_t		Uart_cmd_lum;
} UART_DATA;

extern UART_DATA Uart_data;

void UART_Init();
void UART_Task();
void UART_Reset_CMD();
void UART_Send_CMD();
#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_TASK_H_ */
