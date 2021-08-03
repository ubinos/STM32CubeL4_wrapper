/**
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

#include <ubinos.h>

#if (INCLUDE__APP__myflash_eraseprogram == 1)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"

//
extern char __flash2_start__; /* Set by linker.  */
extern char __flash2_size__; /* Set by linker.  */

#define FLASH_USER_START_ADDR   ((intptr_t) &__flash2_start__)  /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR     ((intptr_t) &__flash2_start__  +  (intptr_t) &__flash2_size__ - 1) /* End @ of user Flash area : sector start address + sector size - 1 */

#define DATA_32                 ((uint32_t)0x12345678)
#define DATA_64                 ((uint64_t)0x1234567812345678)

uint32_t FirstPage = 0, NbOfPages = 0, BankNumber = 0;
uint32_t Address = 0, PAGEError = 0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0;

static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t GetPage(uint32_t Address);
static uint32_t GetBank(uint32_t Address);

//
static void rootfunc(void *arg);
static void task1func(void *arg);
static void task2func(void *arg);

int appmain(int argc, char *argv[])
{
    int r;

    r = task_create(NULL, rootfunc, NULL, task_getmiddlepriority(), 0, "root");
    if (0 != r)
    {
        logme("fail at task_create\n");
    }

    ubik_comp_start();

    return 0;
}

static void rootfunc(void *arg)
{
    int r;

    printf("\n\n\n");
    printf("================================================================================\n");
    printf("myflash_eraseprogram (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    printf("FLASH_USER_START_ADDR = 0x%08x\n", FLASH_USER_START_ADDR);
    printf("FLASH_USER_END_ADDR   = 0x%08x\n", FLASH_USER_END_ADDR);
    printf("\n");

    r = task_create(NULL, task1func, NULL, task_getmiddlepriority(), 0, "task1");
    if (0 != r)
    {
        logme("fail at task_create\n");
    }

    r = task_create(NULL, task2func, NULL, task_getmiddlepriority(), 0, "task2");
    if (0 != r)
    {
        logme("fail at task_create\n");
    }

    /* Initialize LED2 */
    BSP_LED_Init(LED2);

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear OPTVERR bit set on virgin samples */
  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);
  /* Get the 1st page to erase */
  FirstPage = GetPage(FLASH_USER_START_ADDR);
  /* Get the number of pages to erase from 1st page */
  NbOfPages = GetPage(FLASH_USER_END_ADDR) - FirstPage + 1;
  /* Get the bank */
  BankNumber = GetBank(FLASH_USER_START_ADDR);
  /* Fill EraseInit structure*/
  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
  EraseInitStruct.Banks       = BankNumber;
  EraseInitStruct.Page        = FirstPage;
  EraseInitStruct.NbPages     = NbOfPages;

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
  {
    /*
      Error occurred while page erase.
      User can add here some code to deal with this error.
      PAGEError will contain the faulty page and then to know the code error on this page,
      user can call function 'HAL_FLASH_GetError()'
    */
    /* Infinite loop */
    while (1)
    {
      /* Make LED2 blink (100ms on, 2s off) to indicate error in Erase operation */
      BSP_LED_On(LED2);
      HAL_Delay(100);
      BSP_LED_Off(LED2);
      HAL_Delay(2000);
    }
  }

  /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  Address = FLASH_USER_START_ADDR;

  while (Address < FLASH_USER_END_ADDR)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, Address, DATA_64) == HAL_OK)
    {
      Address = Address + 8;
    }
   else
    {
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
      while (1)
      {
        /* Make LED2 blink (100ms on, 2s off) to indicate error in Write operation */
        BSP_LED_On(LED2);
        HAL_Delay(100);
        BSP_LED_Off(LED2);
        HAL_Delay(2000);
      }
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  /* Check if the programmed data is OK
      MemoryProgramStatus = 0: data programmed correctly
      MemoryProgramStatus != 0: number of words not programmed correctly ******/
  Address = FLASH_USER_START_ADDR;
  MemoryProgramStatus = 0x0;

  while (Address < FLASH_USER_END_ADDR)
  {
    data32 = *(__IO uint32_t *)Address;

    if (data32 != DATA_32)
    {
      MemoryProgramStatus++;
    }
    Address = Address + 4;
  }

  /*Check if there is an issue to program data*/
  if (MemoryProgramStatus == 0)
  {
    /* No error detected. Switch on LED2*/
    BSP_LED_On(LED2);
  }
  else
  {
    /* Error detected. LED2 will blink with 1s period */
    while (1)
    {
      BSP_LED_On(LED2);
      HAL_Delay(1000);
      BSP_LED_Off(LED2);
      HAL_Delay(1000);
    }
  }

  /* Infinite loop */
  while (1)
  {
  }
}

static void task1func(void *arg)
{
    unsigned int delayms;

    task_sleepms(1000);

    for (unsigned int i = 0;; i++)
    {
        delayms = (rand() % 10 + 1) * 200;
        printf("1: hello world ! (%u) (delay = %4d ms)\n", i, delayms);
        task_sleepms(delayms);
    }
}

static void task2func(void *arg)
{
    unsigned int delayms;

    task_sleepms(1000);

    for (unsigned int i = 0;; i++)
    {
        delayms = (rand() % 10 + 1) * 200;
        printf("2: hello world ! (%u) (delay = %4d ms)\n", i, delayms);
        task_sleepms(delayms);
    }
}

/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  uint32_t page = 0;

  if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
  {
    /* Bank 1 */
    page = (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;
  }
  else
  {
    /* Bank 2 */
    page = (Addr - (FLASH_BASE + FLASH_BANK_SIZE)) / FLASH_PAGE_SIZE;
  }

  return page;
}

/**
  * @brief  Gets the bank of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The bank of a given address
  */
static uint32_t GetBank(uint32_t Addr)
{
  uint32_t bank = 0;

  if (READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_FB_MODE) == 0)
  {
  	/* No Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_1;
    }
    else
    {
      bank = FLASH_BANK_2;
    }
  }
  else
  {
  	/* Bank swap */
    if (Addr < (FLASH_BASE + FLASH_BANK_SIZE))
    {
      bank = FLASH_BANK_2;
    }
    else
    {
      bank = FLASH_BANK_1;
    }
  }

  return bank;
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

#endif /* (INCLUDE__APP__myflash_eraseprogram == 1) */

