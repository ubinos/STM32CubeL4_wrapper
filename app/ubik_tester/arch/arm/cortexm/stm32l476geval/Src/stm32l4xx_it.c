#include <ubinos.h>

#if (INCLUDE__APP__ubik_tester == 1)
#if (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL)
#if (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL)

#include "main.h"
#include "stm32l4xx_it.h"

/**
 * @brief  This function handles DTTY_STM32_UART interrupt request.
 * @param  None
 * @retval None
 */
void DTTY_STM32_UART_IRQHandler(void)
{
    HAL_UART_IRQHandler(&DTTY_STM32_UART_HANDLE);
}

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

#endif /* (UBINOS__BSP__DTTY_TYPE == UBINOS__BSP__DTTY_TYPE__EXTERNAL) */
#endif /* (UBINOS__BSP__BOARD_MODEL == UBINOS__BSP__BOARD_MODEL__STM32L476GEVAL) */
#endif /* (INCLUDE__APP__ubik_tester == 1) */

