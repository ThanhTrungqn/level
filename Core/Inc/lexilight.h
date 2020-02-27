/*
 * lexilight.h
 *
 *  Created on: Feb 10, 2020
 *      Author: tnguyen
 */

#ifndef INC_LEXILIGHT_H_
#define INC_LEXILIGHT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdbool.h>

#define SYSTEM_CLOCK_PER_SECOND 		16000000  //48000000
#define LEXILIGHT_DUTY_INTERVAL 		100		//Level of Luminosity from 0 to 100
#define LEXILIGHT_FREQUENCY_MAX 		120		//Need Value (max +1)
#define LEXILIGHT_FREQUENCY_MIN 		65
#define LEXILIGHT_FREQUENCY_DEFAULT 	80
#define LEXILIGHT_DUTY_DEFAULT 			20
#define LEXILIGHT_DUTY_MAX 				40		//Need value (max + 1)
#define LEXILIGHT_DUTY_MIN 				10
#define LEXILIGHT_ADC_VARIANT			10 	//If variant >  10 value; will update
#define LEXILIGHT_ADC_BIT				10	//Change if Varier

typedef enum
{
	/* Application's state machine's initial state. */
	LIGHT_STATE_INIT=0,			//Initial State
	LIGHT_STATE_WAIT_500_MS,	//Wait 500ms after Initial
	LIGHT_STATE_SERVICE,		//Ready for Service
	LIGHT_STATE_ON,				//Turn On Light LexiLight
	LIGHT_STATE_STANDARD,		//Turn Light Normal
	LIGHT_STATE_LEXI,			//Turn Light Lexi
	LIGHT_STATE_OFF,			//Turn Off Light
	LIGHT_STATE_ERROR			//Error

} LIGHT_STATES;

typedef enum
{
	/* Light Luminosity Level */
	LIGHT_LUM_LEVEL_0 = 0,
	LIGHT_LUM_LEVEL_1,
	LIGHT_LUM_LEVEL_2
} LIGHT_LUM_LEVEL;

typedef struct {
	unsigned long system_clock;
    unsigned int duty;
    unsigned int freq;
    unsigned int duty_cmd;
    unsigned int freq_cmd;
    unsigned int duty_max;
    unsigned int duty_min;
    unsigned int freq_max;
    unsigned int freq_min;
	unsigned int adc_duty_raw;
	unsigned int adc_freq_raw;
	unsigned int adc_duty_new;
	unsigned int adc_freq_new;
	unsigned int adc_variant;
	unsigned int adc_number_step;
	unsigned int timer_on_off_start;
	unsigned int timer_on_off_end;
	unsigned int pwm_led_driver;
	unsigned int lum_value;
	LIGHT_STATES state;
	LIGHT_LUM_LEVEL lum_level;
} LEXILIGHT_DATA;

void Lexi_RecordTime_ON_OFF_Start(void);
void Lexi_RecordTime_ON_OFF_End(void);
bool Lexi_Detect_Long_Push_ON_OFF (void);


void Lexi_Task (TIM_HandleTypeDef htim_pwm_led, TIM_HandleTypeDef htim_pwm_lum_driver);
void Lexi_Init_Data (void);
void Lexi_DO_LED_PWM (TIM_HandleTypeDef htim);
void Lexi_DO_Standard_PWM (TIM_HandleTypeDef htim);
void Lexi_DO_PWM_LUM_DRIVER (TIM_HandleTypeDef htim);
//Get function
unsigned int Lexi_Get_Duty();
unsigned int Lexi_Get_Freq();
unsigned int Lexi_Get_Luminosity();
unsigned int Lexi_Get_Led_State_ON();
//Set function
void Lexi_Set_State_OFF ();
void Lexi_Set_State_ON ();
void Lexi_Set_State_STANDARD ();
void Lexi_Set_Duty( unsigned int value );
void Lexi_Set_State_LEXI ();
void Lexi_Set_Freq( unsigned int value);
void Lexi_Set_Luminosity( unsigned int value);
#endif /* INC_LEXILIGHT_H_ */
