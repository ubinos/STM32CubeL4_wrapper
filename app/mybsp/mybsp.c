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

#if (INCLUDE__APP__mybsp == 1)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "main.h"

extern UART_HandleTypeDef hDiscoUart;
#ifdef __GNUC__
/* With GCC/RAISONANCE, small msg_info (option LD Linker->Libraries->Small msg_info
 set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */

static void task0func(void *arg);
static void task1func(void *arg);
static void task2func(void *arg);

int appmain(int argc, char *argv[]) {
	int r;

	HAL_Init();
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
	printf("\n\n\r\n");
	printf("================================================================================\r\n");
	printf("mybsp (build time: %s %s)\r\n", __TIME__, __DATE__);
	printf("================================================================================\r\n");
	printf("\r\n");
#if (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1)
	r = heap_printheapinfo(NULL);
	if (0 == r) {
		printf("\r\n");
		printf("================================================================================\r\n");
		printf("\r\n");
	}
#endif /* (UBINOS__UBICLIB__USE_MALLOC_RETARGETING == 1) */

	srand(time(NULL));

	r = task_create(NULL, task0func, NULL, task_getmiddlepriority(), 0, "task0");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, task1func, NULL, task_getmiddlepriority(), 0, "task1");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	r = task_create(NULL, task2func, NULL, task_getmiddlepriority(), 0, "task2");
	if (0 != r) {
		logme("fail at task_create\r\n");
	}

	ubik_comp_start();

	return 0;
}

static void task0func(void *arg) {
	printf("Press User button to put LED2 ON \n");

	while (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_RESET)
		;
	while (BSP_PB_GetState(BUTTON_USER) == GPIO_PIN_SET)
		;
	BSP_LED_On(LED2);

	for (unsigned int i = 0;; i++) {
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

static void task1func(void *arg) {
	unsigned int delayms;

	task_sleepms(1000);

	for (unsigned int i = 0;; i++) {
		delayms = (rand() % 10 + 1) * 200;
		printf("1: hello world ! (%u) (delay = %4d ms)\r\n", i, delayms);
		task_sleepms(delayms);
	}
}

static void task2func(void *arg) {
	unsigned int delayms;

	task_sleepms(1000);

	for (unsigned int i = 0;; i++) {
		delayms = (rand() % 10 + 1) * 200;
		printf("2: hello world ! (%u) (delay = %4d ms)\r\n", i, delayms);
		task_sleepms(delayms);
	}
}

/**
 * @brief Retargets the C library msg_info function to the USART.
 * @param None
 * @retval None
 */
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the serial port and Loop until the end of transmission */
	while (HAL_OK != HAL_UART_Transmit(&hDiscoUart, (uint8_t*) &ch, 1, 30000)) {
		;
	}
	return ch;
}

/**
 * @brief Retargets the C library scanf function to the USART.
 * @param None
 * @retval None
 */
GETCHAR_PROTOTYPE {
	/* Place your implementation of fgetc here */
	/* e.g. readwrite a character to the USART2 and Loop until the end of transmission */
	uint8_t ch = 0;
	while (HAL_OK != HAL_UART_Receive(&hDiscoUart, (uint8_t*) &ch, 1, 30000)) {
		;
	}
	return ch;
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void Error_Handler(void) {
	/* User can add his own implementation to report the HAL error return state */
	printf("!!! ERROR !!!\n");
	while (1) {
	}
}

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1) {
	}
}
#endif

/**
 * @brief  Gets numeric values from the Hyperterminal.
 * @param  Maximun value allowed (value)
 * @retval The character received
 */
uint32_t Serial_Scanf(uint32_t value) {
	uint16_t tmp = 0;

	tmp = getchar();

	if (tmp > value) {
		printf("\n\r  !!! Please enter valid number between 0 and %lu \n", value);
		return 0xFF;
	}
	return tmp;
}

int _read (int file, char *ptr, int len)
{
	/* The I/O library uses an internal buffer */
	/* It asks for 1024 characters even if only getc() is used. */
	/* If we use a for(;;) loop on the number of characters requested, */
	/* the user is forced to enter the exact number requested, even if only one is needed. */
	/* So here we return only 1 character even if requested length is > 1 */
	*ptr = __io_getchar();

	return 1;
}

int _write(int file, char *ptr, int len)
{
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

#endif /* (INCLUDE__APP__mybsp == 1) */

