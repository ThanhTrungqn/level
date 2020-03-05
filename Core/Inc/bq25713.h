/*
 * bq25713.h
 *
 *  Created on: Feb 12, 2020
 *      Author: tnguyen
 */

#ifndef INC_BQ25713_H_
#define INC_BQ25713_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef struct {
	I2C_HandleTypeDef BQ25713_I2C;
	uint8_t I2C_Address;
	uint8_t Manufacture_Id;
	uint8_t	Device_Id;
	uint8_t adc_vbat;
	uint8_t active_fast_charge;
} BQ25713_DATA;


#define BQ25713_I2C_ADDRESS					0xD6	//9.5
#define BQ25713_MANUFACTURE_ID				0x40	//9.6.13
#define BQ25713_DEVICE_ID					0x88
/* Registers */
#define BQ25713_REG_CHARGE_OPTION_0			0x00	//9.6.1.1
#define BQ25713_REG_CHARGE_OPTION_1			0x30	//9.6.1.2
#define BQ25713_REG_CHARGE_OPTION_2			0x32	//9.6.1.3
#define BQ25713_REG_CHARGE_OPTION_3			0x34	//9.6.1.4
#define BQ25713_REG_PROCHOT_OPTION_0		0x36	//9.6.1.5
#define BQ25713_REG_PROCHOT_OPTION_1		0x38	//9.6.1.6
#define BQ25713_REG_ADC_OPTION				0x3A	//9.6.1.7
#define BQ25713_REG_CHARGER_STATUS			0x20	//9.6.2.1
#define BQ25713_REG_PROCHOT_STATUS			0x22	//9.6.2.2
#define BQ25713_REG_CHARGE_CURRENT			0x02	//9.6.3
#define BQ25713_REG_MAX_CHARGE_VOLTAGE		0x04	//9.6.4
#define BQ25713_REG_MIN_SYSTEM_VOLTAGE		0x0C	//9.6.5
#define BQ25713_REG_IIN_HOST				0x0E	//9.6.6.1.1
#define BQ25713_REG_IIN_DPM					0x24	//9.6.6.1.2
#define BQ25713_REG_INPUT_VOLTAGE			0x0A	//9.6.6.1.3
#define BQ25713_REG_OTG_VOLTAGE				0x06	//9.6.7
#define BQ25713_REG_OTG_CURRENT				0x08	//9.6.8
#define BQ25713_REG_ADC_VBUS_PSYS			0x26	//9.6.9
#define BQ25713_REG_ADC_IBAT				0x28	//9.6.10
#define BQ25713_REG_ADC_CMPIN_IIN			0x2A	//9.6.11
#define BQ25713_REG_ADC_VSYS_VBAT			0x2C	//9.6.12
#define BQ25713_REG_MANUFACTURER_ID			0x2E	//9.6.13
#define BQ25713_REG_DEVICE_ADDRESS			0x2F

/* Function */

void BQ25713_Init(I2C_HandleTypeDef i2c_handle);
void BQ25713_Task();
void read_register_16(uint8_t register_pointer, uint8_t* receive_buffer);
void write_register_16(uint8_t register_pointer, uint16_t register_value);
void BQ25713_Default_Charge();
uint8_t BQ25713_Get_VBat();
#endif /* INC_BQ25713_H_ */
