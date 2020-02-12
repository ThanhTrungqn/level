/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CMD_LED2_Pin GPIO_PIN_2
#define CMD_LED2_GPIO_Port GPIOE
#define CMD_LED3_Pin GPIO_PIN_3
#define CMD_LED3_GPIO_Port GPIOE
#define CMD_LED4_Pin GPIO_PIN_4
#define CMD_LED4_GPIO_Port GPIOE
#define CMD_LED5_Pin GPIO_PIN_5
#define CMD_LED5_GPIO_Port GPIOE
#define CMD_LED6_Pin GPIO_PIN_6
#define CMD_LED6_GPIO_Port GPIOE
#define CHRG_OK_Pin GPIO_PIN_13
#define CHRG_OK_GPIO_Port GPIOC
#define PROCHOT_Pin GPIO_PIN_14
#define PROCHOT_GPIO_Port GPIOC
#define EN_OTG_Pin GPIO_PIN_15
#define EN_OTG_GPIO_Port GPIOC
#define CMPOUT_Pin GPIO_PIN_1
#define CMPOUT_GPIO_Port GPIOC
#define LCD_RESET_Pin GPIO_PIN_2
#define LCD_RESET_GPIO_Port GPIOA
#define SHDN_CONTROL_Pin GPIO_PIN_4
#define SHDN_CONTROL_GPIO_Port GPIOC
#define TP_RESET_Pin GPIO_PIN_9
#define TP_RESET_GPIO_Port GPIOD
#define TP_INT_Pin GPIO_PIN_11
#define TP_INT_GPIO_Port GPIOD
#define FLT_Pin GPIO_PIN_12
#define FLT_GPIO_Port GPIOD
#define EN_DRIVER_Pin GPIO_PIN_13
#define EN_DRIVER_GPIO_Port GPIOD
#define CMD_ON_OFF_Pin GPIO_PIN_14
#define CMD_ON_OFF_GPIO_Port GPIOD
#define POWER_OK3_Pin GPIO_PIN_9
#define POWER_OK3_GPIO_Port GPIOA
#define POWER_OK2_Pin GPIO_PIN_10
#define POWER_OK2_GPIO_Port GPIOA
#define ALIM_CLE_USB_Pin GPIO_PIN_11
#define ALIM_CLE_USB_GPIO_Port GPIOC
#define CS_LCD_Pin GPIO_PIN_0
#define CS_LCD_GPIO_Port GPIOD
#define CMD_ALIM_LCD_Pin GPIO_PIN_1
#define CMD_ALIM_LCD_GPIO_Port GPIOD
#define CMD_ALIM_BLE_Pin GPIO_PIN_6
#define CMD_ALIM_BLE_GPIO_Port GPIOD
#define CS_FLASH_Pin GPIO_PIN_7
#define CS_FLASH_GPIO_Port GPIOD
#define CMD_WP_MEM_Pin GPIO_PIN_5
#define CMD_WP_MEM_GPIO_Port GPIOB
#define CMD_LED1_Pin GPIO_PIN_1
#define CMD_LED1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
