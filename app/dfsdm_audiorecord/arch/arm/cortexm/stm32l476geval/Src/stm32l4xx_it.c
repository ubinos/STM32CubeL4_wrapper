#include <ubinos.h>

#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL)

#include "main.h"
#include "stm32l4xx_it.h"

extern DMA_HandleTypeDef hLeftDma;
extern DMA_HandleTypeDef hRightDma;
extern SAI_HandleTypeDef SaiHandle;

#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

/**
 * @brief  This function handles DTTY_STM32_UART interrupt request.
 * @param  None
 * @retval None
 */
void DTTY_STM32_UART_IRQHandler(void)
{
    HAL_UART_IRQHandler(&DTTY_STM32_UART_HANDLE);
}

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */

#if (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC)

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    HAL_IncTick();
}

#endif /* (UBINOS__UBIK__TICK_TYPE == UBINOS__UBIK__TICK_TYPE__RTC) */

/**
  * @brief  This function handles DMA1_Channel4 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel4_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hLeftDma);
}

/**
  * @brief  This function handles DMA1_Channel5 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hRightDma);
}

/**
  * @brief  This function handles SAI DMA interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Channel2_IRQHandler(void)
{ 
  HAL_DMA_IRQHandler(SaiHandle.hdmatx);
}

#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) */

