/*
 * lexilight.c
 *
 *  Created on: Feb 10, 2020
 *      Author: tnguyen
 */

/**
  ******************************************************************************
  * @file           : lexilight.c
  * @brief          : Main LED program
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "lexilight.h"


LEXILIGHT_DATA lexilight;

void Lexi_Init_Data() {
	lexilight.system_clock 		= SYSTEM_CLOCK_PER_SECOND;
	lexilight.duty_min 			= LEXILIGHT_DUTY_MIN;
	lexilight.duty_max 			= LEXILIGHT_DUTY_MAX;
	lexilight.duty_cmd 			= LEXILIGHT_DUTY_DEFAULT;
	lexilight.duty				= 30;
	lexilight.freq_max 			= LEXILIGHT_FREQUENCY_MAX;
	lexilight.freq_min 			= LEXILIGHT_FREQUENCY_MIN;
	lexilight.freq_cmd 			= LEXILIGHT_FREQUENCY_DEFAULT;
	lexilight.freq				= 90;
	lexilight.lum_level 		= LIGHT_LUM_LEVEL_0;
	lexilight.lum_value			= 90;
	lexilight.state 			= LIGHT_STATE_WAIT_500_MS;
}


void Lexi_Task (TIM_HandleTypeDef htim_pwm_led, TIM_HandleTypeDef htim_pwm_lum_driver){

	switch (lexilight.state)
	{
		case LIGHT_STATE_ERROR:
		case LIGHT_STATE_INIT:
			Lexi_Init_Data();
			lexilight.state = LIGHT_STATE_WAIT_500_MS;
			break;

		case LIGHT_STATE_WAIT_500_MS:
			HAL_Delay(500);
			lexilight.state = LIGHT_STATE_SERVICE;
			break;

		case LIGHT_STATE_SERVICE:

			//Get pwm defaut or eeprom
			Lexi_DO_LED_PWM (htim_pwm_led);
			Lexi_DO_PWM_LUM_DRIVER(htim_pwm_lum_driver);
			lexilight.state = LIGHT_STATE_OFF;
			break;

		case LIGHT_STATE_LEXI:
			Lexi_DO_LED_PWM (htim_pwm_led);
			Lexi_DO_PWM_LUM_DRIVER(htim_pwm_lum_driver);
			//Turn On EN_DRIVER
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
			break;

		case LIGHT_STATE_ON:
		case LIGHT_STATE_STANDARD:
			Lexi_DO_Standard_PWM(htim_pwm_led);
			Lexi_DO_PWM_LUM_DRIVER(htim_pwm_lum_driver);
			//Turn On EN_DRIVER
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13,GPIO_PIN_SET);
			break;

		case LIGHT_STATE_OFF:
			Lexi_DO_LED_PWM (htim_pwm_led);
			Lexi_DO_PWM_LUM_DRIVER(htim_pwm_lum_driver);
			//Turn OFF EN_DRIVER
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
			break;
		default:
			lexilight.state = LIGHT_STATE_ERROR;
			break;
		}
}

void Lexi_DO_LED_PWM (TIM_HandleTypeDef htim){
	//Check update Freq
	if ((	lexilight.freq_cmd >= lexilight.freq_min)
			&& (lexilight.freq_cmd <= lexilight.freq_max))
			//&& (lexilight.freq != lexilight.freq_cmd))
	{
		lexilight.freq = lexilight.freq_cmd;	//Update New value of ADC Duty;
		int prescaler = (uint16_t)(lexilight.system_clock/(lexilight.freq*100) - 1);
		__HAL_TIM_SET_PRESCALER(&htim, prescaler);
		lexilight.freq = lexilight.freq_cmd;
	}

	//Check update Dutycycle
	if ((	lexilight.duty_cmd >= lexilight.duty_min)
			&& (lexilight.duty_cmd <= lexilight.duty_max))
			//&& (lexilight.duty != lexilight.duty_cmd))
	{
		lexilight.duty = lexilight.duty_cmd;
		__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1,lexilight.duty);
	}
}

void Lexi_DO_Standard_PWM (TIM_HandleTypeDef htim){
		int prescaler = 59;		//Set frequency 119 = 4KHZ
		__HAL_TIM_SET_PRESCALER(&htim, prescaler);
		//__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_2, lexilight.duty);
		__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, 100);

}

void Lexi_DO_PWM_LUM_DRIVER (TIM_HandleTypeDef htim){

	uint8_t value = lexilight.lum_value; // Value from 0 to 100;
	value = 100 - value;
	__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, value);



	//Todo :  do the  signal PWM_LUM_DRIVER
	/*
	unsigned int lux_cmd = 0;
	unsigned int value = 0;
	unsigned int value_2 = 0;
	switch (lexilight.lum_level){
		case LIGHT_LUM_LEVEL_0:
			if (lexilight.duty <= 20){
				lux_cmd =  900 + (1400 - 900)*(lexilight.duty - 10)/10;
			}
			else {
				lux_cmd =  1400;
			}
			//Calcule value I en fonction de dutycycle
			if (lexilight.state  == LIGHT_STATE_STANDARD){
				value_2 = (unsigned int)(lux_cmd / 100) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			else{
				value_2 = (unsigned int)(lux_cmd / lexilight.duty) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, value);
			break;

		case LIGHT_LUM_LEVEL_1:
			//Calculate lux max
			if (lexilight.duty <= 20){
				lux_cmd =  1000 + (2200 - 1000)*(lexilight.duty - 10)/10;
			}
			else {
				lux_cmd =  2200;
			}
			//Calcule value I en fonction de dutycycle
			if (lexilight.state  == LIGHT_STATE_STANDARD){
				value_2 = (unsigned int)(lux_cmd / 100) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			else{
				value_2 = (unsigned int)(lux_cmd / lexilight.duty) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, value);
			break;

		case LIGHT_LUM_LEVEL_2:
			//Calculate lux max
			if (lexilight.duty <= 20){
				lux_cmd =  1200 + (2800 - 1200)*(lexilight.duty - 10)/10;
			}
			else {
				lux_cmd =  2800;
			}
			//Calcule value I en fonction de dutycycle
			if (lexilight.state  == LIGHT_STATE_STANDARD){
				value_2 = (unsigned int)(lux_cmd / 100) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			else{
				value_2 = (unsigned int)(lux_cmd / lexilight.duty) ;
				value  = (unsigned int)((140 - value_2)*0.77);
				lexilight.pwm_led_driver = value;
			}
			__HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_3, value);
			break;

		default:
			break;
	}
	*/
}
//Get function
unsigned int Lexi_Get_Duty(){
	return lexilight.duty;
}
unsigned int Lexi_Get_Freq(){
	return lexilight.freq;
}
unsigned int Lexi_Get_Luminosity(){
	return (lexilight.lum_value);
}
unsigned int Lexi_Get_Led_State(){
	if (lexilight.state == LIGHT_STATE_LEXI){
		return 2;
	}
	else if ((lexilight.state == LIGHT_STATE_ON) || (lexilight.state == LIGHT_STATE_STANDARD)){
		return 1;
	}
	else if (lexilight.state == LIGHT_STATE_OFF) {
		return 0;
	}
	else{
		return 0;
	}
}
//Set function
void Lexi_Set_State_OFF (){
	lexilight.state = LIGHT_STATE_OFF;
}
void Lexi_Set_State_ON (){
	lexilight.state = LIGHT_STATE_ON;
}
void Lexi_Set_State_STANDARD (){
	lexilight.state = LIGHT_STATE_STANDARD;
}
void Lexi_Set_State_LEXI (){
	lexilight.state = LIGHT_STATE_LEXI;
}
void Lexi_Set_Duty( unsigned int value){
	if (value >=40){
		lexilight.duty_cmd  = 40;
	}
	else{
		lexilight.duty_cmd  = value;
	}
}

void Lexi_Set_Freq( unsigned int value){
	if (value >=120){
			lexilight.freq_cmd  = 120;
	}
	else if (value <=65){
		lexilight.freq_cmd  = 65;
	}
	else{
		lexilight.freq_cmd  = value;
	}
}

void Lexi_Set_Luminosity( unsigned int value){
	lexilight.lum_value =  value;
}
/*
void Lexi_RecordTime_ON_OFF_Start(){
	lexilight.timer_on_off_start = HAL_GetTick ();
}
void Lexi_RecordTime_ON_OFF_End(){
	lexilight.timer_on_off_end = HAL_GetTick ();
}
bool Lexi_Detect_Long_Push_ON_OFF (){
	if ((lexilight.timer_on_off_end - lexilight.timer_on_off_start) > 1500 ) //Time in milisecond
	{
		return true;
	}
	else
	{
		return false;
	}
}
*/
