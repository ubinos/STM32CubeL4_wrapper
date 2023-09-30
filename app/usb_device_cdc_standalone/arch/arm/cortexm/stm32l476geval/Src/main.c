/*
 * Copyright (c) 2021 Sung Ho Park and CSOS
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL)

#include "main.h"

#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

#if (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1)

UART_HandleTypeDef DTTY_STM32_UART_HANDLE;

/**
 * @brief  Tx Transfer completed callback
 * @param  huart: UART handle.
 * @note   This example shows a simple way to report end of DMA Tx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_tx_callback();
    }
}

/**
 * @brief  Rx Transfer completed callback
 * @param  huart: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_rx_callback();
    }
}

/**
 * @brief  UART error callbacks
 * @param  huart: UART handle
 * @note   This example shows a simple way to report transfer error, and you can
 *         add your own implementation.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == DTTY_STM32_UART)
    {
        dtty_stm32_uart_err_callback();
    }
}
#endif /* (STM32CUBEL4__DTTY_STM32_UART_ENABLE == 1) */

#if (STM32CUBEL4__USE_HAL_USBD == 1)

USBD_HandleTypeDef USBD_HANDLE;
PCD_HandleTypeDef PCD_HANDLE;
TIM_HandleTypeDef TIM_HANDLE;

// void usb_init()
// {
//   /* Enable Power Clock*/
//   __HAL_RCC_PWR_CLK_ENABLE();
  
//   /* enable USB power on Pwrctrl CR2 register */
//   HAL_PWREx_EnableVddUSB();

//   /* Init Device Library */
//   USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
//   /* Add Supported Class */
//   USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
//   /* Add CDC Interface Class */
//   USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
//   /* Start Device Process */
//   USBD_Start(&USBD_Device);
// }

// /**
//   * @brief  This function is executed in case of error occurrence.
//   * @param  None
//   * @retval None
//   */
// static void Error_Handler(void)
// {
//   while (1)
//   {
//   }
// }

// /**
//   * @brief  System Clock Configuration
//   *         The system Clock is configured as follow : 
//   *
//   *         If define USB_USE_LSE_MSI_CLOCK enabled:
//   *            System Clock source            = PLL (MSI)
//   *            SYSCLK(Hz)                     = 80000000
//   *            HCLK(Hz)                       = 80000000
//   *            AHB Prescaler                  = 1
//   *            APB1 Prescaler                 = 1
//   *            APB2 Prescaler                 = 2
//   *            MSI Frequency(Hz)              = 4800000
//   *            LSE Frequency(Hz)              = 32768
//   *            PLL_M                          = 6
//   *            PLL_N                          = 40
//   *            PLL_P                          = 7
//   *            PLL_Q                          = 4
//   *            PLL_R                          = 4
//   *            Flash Latency(WS)              = 4
//   * 
//   *         If define USB_USE_HSE_CLOCK enabled:
//   *            System Clock source            = PLL (HSE)
//   *            SYSCLK(Hz)                     = 80000000
//   *            HCLK(Hz)                       = 80000000
//   *            AHB Prescaler                  = 1
//   *            APB1 Prescaler                 = 1
//   *            APB2 Prescaler                 = 2
//   *            HSE Frequency(Hz)              = 8000000
//   *            PLL_M                          = 1
//   *            PLL_N                          = 20
//   *            PLL_P                          = 7
//   *            PLL_Q                          = 4
//   *            PLL_R                          = 2
//   *            Flash Latency(WS)              = 4
//   * 
//   * @param  None
//   * @retval None
//   */
// void SystemClock_Config(void)
// {
//   RCC_ClkInitTypeDef RCC_ClkInitStruct;
//   RCC_OscInitTypeDef RCC_OscInitStruct;
//   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

// #if defined (USB_USE_LSE_MSI_CLOCK)
 
//   /* Enable the LSE Oscilator */
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
//   RCC_OscInitStruct.LSEState = RCC_LSE_ON;
//   RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_OFF;
//   HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
//   /* Enable the CSS interrupt in case LSE signal is corrupted or not present */
//   HAL_RCCEx_DisableLSECSS();
  
//   /* Enable MSI Oscillator and activate PLL with MSI as source */
//   RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
//   RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
//   RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
//   RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_11;
//   RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_MSI;
//   RCC_OscInitStruct.PLL.PLLM            = 6;
//   RCC_OscInitStruct.PLL.PLLN            = 40;
//   RCC_OscInitStruct.PLL.PLLP            = 7;
//   RCC_OscInitStruct.PLL.PLLQ            = 4;
//   RCC_OscInitStruct.PLL.PLLR            = 4;
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }

//   /* Enable MSI Auto-calibration through LSE */
//   HAL_RCCEx_EnableMSIPLLMode();

//   /* Select MSI output as USB clock source */
//   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
//   PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_MSI;
//   HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

//   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
//   clocks dividers */
//   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
//   {
//     Error_Handler();
//   }
  
// #elif defined (USB_USE_HSE_CLOCK)
  
//   /* Enable HSE Oscillator and activate PLL with HSE as source */
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//   RCC_OscInitStruct.PLL.PLLM = 1;
//   RCC_OscInitStruct.PLL.PLLN = 20;
//   RCC_OscInitStruct.PLL.PLLR = 2;
//   RCC_OscInitStruct.PLL.PLLP = 7;
//   RCC_OscInitStruct.PLL.PLLQ = 4;  
  
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//   {
//     Error_Handler();
//   }
  
//   /* Select PLLSAI output as USB clock source */
//   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
//   PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1N = 24;
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1Q = 4; 
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1P = 1;
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1M = 1;
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
//   PeriphClkInitStruct.PLLSAI1.PLLSAI1ClockOut= RCC_PLLSAI1_48M2CLK;
//   if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct)!= HAL_OK)
//   {
//     Error_Handler();
//   }
  
//   /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
//   clocks dividers */
//   RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
//   {
//     Error_Handler();
//   }
  
// #endif /* USB_USE_LSE_MSI_CLOCK */
// }

#endif /* (STM32CUBEL4__USE_HAL_USBD == 1) */

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) */

