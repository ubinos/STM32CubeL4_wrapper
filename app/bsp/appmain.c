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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"

extern UART_HandleTypeDef hDiscoUart;

static void rootfunc(void *arg);
static void task1func(void *arg);
static void task2func(void *arg);
static void task3func(void *arg);

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

    ubik_settickhookfunc(HAL_IncTick);

    /* Configure the User LED */
    BSP_LED_Init(LED2);

    /* Configure the User Button in GPIO Mode */
    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

    /* Initialize all configured peripherals */
    hDiscoUart.Instance = DISCOVERY_COM1;
    hDiscoUart.Init.BaudRate = 115200;
    hDiscoUart.Init.WordLength = UART_WORDLENGTH_8B;
    hDiscoUart.Init.StopBits = UART_STOPBITS_1;
    hDiscoUart.Init.Parity = UART_PARITY_NONE;
    hDiscoUart.Init.Mode = UART_MODE_TX_RX;
    hDiscoUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    hDiscoUart.Init.OverSampling = UART_OVERSAMPLING_16;
    hDiscoUart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    hDiscoUart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    BSP_COM_Init(COM1, &hDiscoUart);

    //
    printf("\n\n\n");
    printf("================================================================================\n");
    printf("bsp (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    srand(time(NULL));

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

    r = task_create(NULL, task3func, NULL, task_getmiddlepriority(), 0, "task3");
    if (0 != r)
    {
        logme("fail at task_create\n");
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

static void task3func(void *arg)
{
    printf("Press User button to put LED2 ON \n");

    while (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET);
    while (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET);
    BSP_LED_On(LED2);

    for (unsigned int i = 0;; i++)
    {
        QSPI_demo();
        QSPI_MemoryMapped_demo();
        Temperature_Test();
        Humidity_Test();
        Pressure_Test();
        Magneto_Test();
        Gyro_Test();
        Accelero_Test();
    }
}

/**
 * @brief  Gets numeric values from the Hyperterminal.
 * @param  Maximun value allowed (value)
 * @retval The character received
 */
uint32_t Serial_Scanf(uint32_t value)
{
    uint16_t tmp = 0;

    tmp = getchar();

    if (tmp > value)
    {
        printf("\n  !!! Please enter valid number between 0 and %lu \n", value);
        return 0xFF;
    }
    return tmp;
}

