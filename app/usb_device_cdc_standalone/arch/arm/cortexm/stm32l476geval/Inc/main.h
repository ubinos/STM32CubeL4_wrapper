/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license SLA0044,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        http://www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include <ubinos.h>

#include "stm32l4xx_hal.h"
#include "stm32l476g_eval.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)

/* Definition for DTTY_STM32_UART */

#if (UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER == 1)

#define DTTY_STM32_UART                         USART1
#define DTTY_STM32_UART_HANDLE                  huart1

#define DTTY_STM32_UART_CLK_ENABLE()            __HAL_RCC_USART1_CLK_ENABLE()
#define DTTY_STM32_UART_RX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define DTTY_STM32_UART_TX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define DTTY_STM32_UART_FORCE_RESET()           __HAL_RCC_USART1_FORCE_RESET()
#define DTTY_STM32_UART_RELEASE_RESET()         __HAL_RCC_USART1_RELEASE_RESET()

#define DTTY_STM32_UART_TX_Pin                  GPIO_PIN_6
#define DTTY_STM32_UART_TX_GPIO_Port            GPIOB
#define DTTY_STM32_UART_TX_AF                   GPIO_AF7_USART1
#define DTTY_STM32_UART_RX_Pin                  GPIO_PIN_7
#define DTTY_STM32_UART_RX_GPIO_Port            GPIOB
#define DTTY_STM32_UART_RX_AF                   GPIO_AF7_USART1

#define DTTY_STM32_UART_IRQn                    USART1_IRQn
#define DTTY_STM32_UART_IRQHandler              USART1_IRQHandler

#else

#error "Unsupported UBINOS__BSP__STM32_DTTY_USARTx_INSTANCE_NUMBER"

#endif

extern UART_HandleTypeDef DTTY_STM32_UART_HANDLE;

void dtty_stm32_uart_rx_callback(void);
void dtty_stm32_uart_tx_callback(void);
void dtty_stm32_uart_err_callback(void);

#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */

#if (STM32CUBEL4__USE_HAL_USBD == 1)

#define USBD_HANDLE                             USBD_Device
#define PCD_HANDLE                              hpcd

extern USBD_HandleTypeDef USBD_HANDLE;
extern PCD_HandleTypeDef PCD_HANDLE;

extern sem_pt usbd_write_sem;

#endif /* (STM32CUBEL4__USE_HAL_USBD == 1) */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
