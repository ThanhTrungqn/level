/*
 * bq25713.c
 *
 *  Created on: Feb 12, 2020
 *      Author: tnguyen
 */
#include "bq25713.h"


BQ25713_DATA BQ25713;

void BQ25713_Init(I2C_HandleTypeDef i2c_handle){
	//Initialize I2C Handle
	BQ25713.BQ25713_I2C = i2c_handle;
	BQ25713.Device_Id = BQ25713_DEVICE_ID;
	BQ25713.Manufacture_Id = BQ25713_MANUFACTURE_ID;
	BQ25713.I2C_Address = BQ25713_I2C_ADDRESS;
	BQ25713.active_fast_charge = 0;

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET);


	uint8_t data[2];
	data[0] = 0x00;     // LSB byte of 16bit đata => Fist byte
	data[1] = 0x00;  	// MSB byte of 16bit data => Second byte
	uint16_t value_write = 0x0000;
	//Check if this is BQ25713 driver?
	read_register_16(BQ25713_REG_MANUFACTURER_ID , data);
	if (( data[0] == BQ25713.Manufacture_Id) && (data[1] == BQ25713.Device_Id )){

		//Set VSYSMIN = 12.288V (REG0x0D/0C),
		value_write = 0x0030;
		write_register_16( BQ25713_REG_MIN_SYSTEM_VOLTAGE , value_write);
		//SET VBAT = 16.8 V (REG0x05/04).   0xA041;
		value_write = 0x0040;
		write_register_16( BQ25713_REG_MAX_CHARGE_VOLTAGE , value_write);
		read_register_16 (BQ25713_REG_MAX_CHARGE_VOLTAGE , data);

		value_write = 0x0018;
		write_register_16 (BQ25713_REG_IIN_HOST , value_write);
		read_register_16 (BQ25713_REG_IIN_HOST , data);
		read_register_16 (BQ25713_REG_CHARGE_OPTION_0 , data);

		value_write = 0x0E87;
		write_register_16( BQ25713_REG_CHARGE_OPTION_0 , value_write);

		value_write = 0xFFE0;
		write_register_16( BQ25713_REG_ADC_OPTION , value_write);

		//BQ25713_Default_Charge();
	}
}

void BQ25713_Default_Charge(){
	//When have charge
	//Set I_CHAGE = 0 Reg 0x02/03;
	uint16_t value_write = 0x0000;
	value_write = 0x0000;
	write_register_16( BQ25713_REG_CHARGE_CURRENT , value_write);
	//Set VSYSMIN = 12.288V (REG0x0D/0C),  0038 = > 0x0030 pour 12.288  =>0x003F =  14V
	value_write = 0x0030;
	write_register_16( BQ25713_REG_MIN_SYSTEM_VOLTAGE , value_write);
	//SET VBAT = 16.8 V (REG0x05/04).   0xA041;
	value_write = 0x0041;
	write_register_16( BQ25713_REG_MAX_CHARGE_VOLTAGE , value_write);

	uint8_t data[2];
		data[0] = 0x00;     // LSB byte of 16bit đata => Fist byte
		data[1] = 0x00;  	// MSB byte of 16bit data => Second byte

	//Disable ILIM_HIZ pin to set input current limit. (REG0x33/32 BIT7=0)
	value_write = 0x3702;
	write_register_16( BQ25713_REG_CHARGE_OPTION_2 , value_write);
	//Set I_CHAGE =>  512 = 0x0002 ; 256 = 0x0001 ; 1024 = 0x0004
	value_write = 0x0002;
	write_register_16( BQ25713_REG_CHARGE_CURRENT , value_write);

	read_register_16 (BQ25713_REG_CHARGE_CURRENT , data);
	read_register_16 (BQ25713_REG_IIN_HOST , data);

	read_register_16 (BQ25713_REG_MAX_CHARGE_VOLTAGE , data);
	BQ25713.active_fast_charge = 1;
}

void BQ25713_Task(){

	uint8_t data[2];
	data[0] = 0x00;     // LSB byte of 16bit đata => Fist byte
	data[1] = 0x00;  	// MSB byte of 16bit data => Second byte
	read_register_16 (BQ25713_REG_ADC_VSYS_VBAT , data);
	BQ25713.adc_vbat = (uint8_t)(data[1]*100/255);


	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET){
		if (BQ25713.active_fast_charge == 0 ){
			if (BQ25713.adc_vbat < 75){
				BQ25713_Default_Charge();
				BQ25713.active_fast_charge =1;
			}
		}
			if ((BQ25713.adc_vbat >= 75) && (BQ25713.active_fast_charge ==1)){
				uint16_t value_write = 0x0004;
				write_register_16( BQ25713_REG_CHARGE_CURRENT , value_write);
				BQ25713.active_fast_charge =0;
			}
	}


	if (( BQ25713.adc_vbat >= 0)&&( BQ25713.adc_vbat < 15)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else if (( BQ25713.adc_vbat >= 15)&&( BQ25713.adc_vbat < 30)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else if (( BQ25713.adc_vbat >= 30)&&( BQ25713.adc_vbat < 50)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);

	}
	else if (( BQ25713.adc_vbat >= 50)&&( BQ25713.adc_vbat < 70)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);

	}
	else if (( BQ25713.adc_vbat >= 70)&&( BQ25713.adc_vbat < 85)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else if (( BQ25713.adc_vbat >= 85)&&( BQ25713.adc_vbat <= 100)){
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	data[0] = 0x00;     // LSB byte of 16bit đata => Fist byte
	data[1] = 0x00;  	// MSB byte of 16bit data => Second byte
	read_register_16 (BQ25713_REG_CHARGER_STATUS , data);
	read_register_16 (BQ25713_REG_PROCHOT_STATUS , data);
	read_register_16 (BQ25713_REG_CHARGER_STATUS , data);
}

uint8_t BQ25713_Get_VBat(){
	/*
	if (( BQ25713.adc_vbat >= 0)&&( BQ25713.adc_vbat < 60)){
		return 1;
	}
	else if (( BQ25713.adc_vbat >= 60)&&( BQ25713.adc_vbat < 70)){
		return 2;
	}
	else if (( BQ25713.adc_vbat >= 70)&&( BQ25713.adc_vbat < 80)){
		return 3;
	}
	else if (( BQ25713.adc_vbat >= 80)&&( BQ25713.adc_vbat < 88)){
		return 4;
	}
	else if (( BQ25713.adc_vbat >= 88)&&( BQ25713.adc_vbat < 95)){
		return 5;
	}
	else if (( BQ25713.adc_vbat >= 95)&&( BQ25713.adc_vbat <= 100)){
		return 6;
	}
	*/
	return BQ25713.adc_vbat;
}

void read_register_16(uint8_t register_pointer, uint8_t* receive_buffer)
{
    // first set the register pointer to the register wanted to be read
    HAL_I2C_Master_Transmit(&BQ25713.BQ25713_I2C, BQ25713.I2C_Address, &register_pointer, 1, 100);
    // receive the 2 x 8bit data into the receive buffer
    HAL_I2C_Master_Receive(&BQ25713.BQ25713_I2C, BQ25713.I2C_Address, receive_buffer, 2, 100);
}

void write_register_16(uint8_t register_pointer, uint16_t register_value)
{
    uint8_t data[3];
    data[0] = register_pointer;     // 0x0C in your example
    data[1] = register_value>>8;    // MSB byte of 16bit data
    data[2] = register_value;       // LSB byte of 16bit data
    HAL_I2C_Master_Transmit(&BQ25713.BQ25713_I2C, BQ25713.I2C_Address, data, 3, 100);  // data is the start pointer of our array
}
