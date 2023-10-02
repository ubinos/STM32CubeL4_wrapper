/**
  ******************************************************************************
  * @file    UART/UART_HyperTerminal_DMA/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#include <ubinos.h>

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "stm32l476g_eval.h"
#include "audio.h"
#include "wm8994/wm8994.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

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

#define SaturaLH(N, L, H) (((N)<(L))?(L):(((N)>(H))?(H):(N)))

void DFSDM_Init(void);
void Playback_Init(void);

extern DFSDM_Filter_HandleTypeDef   DfsdmLeftFilterHandle;
extern DFSDM_Filter_HandleTypeDef   DfsdmRightFilterHandle;
extern SAI_HandleTypeDef            SaiHandle;
extern DMA_HandleTypeDef            hSaiDma;
extern AUDIO_DrvTypeDef            *audio_drv;
extern int32_t                      LeftRecBuff[2048];
extern int32_t                      RightRecBuff[2048];
extern int16_t                      PlayBuff[4096];
extern uint32_t                     DmaLeftRecHalfBuffCplt;
extern uint32_t                     DmaLeftRecBuffCplt;
extern uint32_t                     DmaRightRecHalfBuffCplt;
extern uint32_t                     DmaRightRecBuffCplt;
extern uint32_t                     PlaybackStarted;

extern sem_pt dfsm_buf_sem;

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
