/*
 * Copyright (c) 2009 Sung Ho Park
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ubinos.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <main.h>

static void root_func(void *arg);

static void cli_help_hook_func();
static int cli_hook_func(char *str, int len, void *arg);
static int my_command(char *str, int len, void *arg);

extern void usb_init();

int appmain(int argc, char *argv[])
{
    int r;
    (void) r;

    r = task_create(NULL, root_func, NULL, task_getmiddlepriority(), 0, "root");
    ubi_assert(r == 0);

    ubik_comp_start();

    return 0;
}

static void root_func(void *arg)
{
    int r;
    (void) r;

    printf("\n\n\n");
    printf("================================================================================\n");
    printf("usb_device_cdc_standalone (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(cli_hook_func, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(cli_help_hook_func);
    ubi_assert(r == 0);

    r = cli_setprompt("cli_tester> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);

  /* Enable Power Clock*/
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* enable USB power on Pwrctrl CR2 register */
  HAL_PWREx_EnableVddUSB();

  /* Init Device Library */
  USBD_Init(&USBD_Device, &VCP_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);
  
  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  
  /* Start Device Process */
  USBD_Start(&USBD_Device);

}

static int cli_hook_func(char *str, int len, void *arg)
{
    int r = -1;
    char *tmpstr;
    int tmplen;
    char *cmd = NULL;
    int cmdlen;

    tmpstr = str;
    tmplen = len;

    cmd = "mc";
    cmdlen = strlen(cmd);
    if (tmplen == cmdlen && strncmp(tmpstr, cmd, cmdlen) == 0)
    {
        tmpstr = &tmpstr[cmdlen];
        tmplen -= cmdlen;

        r = my_command(tmpstr, tmplen, arg);
    }

    return r;
}

static void cli_help_hook_func()
{
    printf("mc                                      : my command\n");
}

#define TX_BUFFER_SIZE_MAX 1024
uint8_t tx_buffer[TX_BUFFER_SIZE_MAX];

static int my_command(char *str, int len, void *arg)
{
    printf("\n");

    for (int i = 0; i < TX_BUFFER_SIZE_MAX; i++)
    {
        tx_buffer[i] = i % 10 + 'a';
    }

    USBD_CDC_SetTxBuffer(&USBD_Device, (uint8_t*)tx_buffer, 1);
    if(USBD_CDC_TransmitPacket(&USBD_Device) == USBD_OK)
    {
        printf("ok\n");
    }
    else
    {
        printf("fail\n");
    }

    for (int i = 0; i < 1000; )
    {
        USBD_CDC_SetTxBuffer(&USBD_Device, (uint8_t*)tx_buffer, TX_BUFFER_SIZE_MAX);
        if(USBD_CDC_TransmitPacket(&USBD_Device) == USBD_OK)
        {
            i++;
        }
        else
        {
            // printf("fail\r\n");
            // task_sleepms(10);
        }
    }
    printf("ok\n");

    return 0;
}
