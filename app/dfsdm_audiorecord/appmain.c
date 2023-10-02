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
    printf("dfsdm_audiorecord (build time: %s %s)\n", __TIME__, __DATE__);
    printf("================================================================================\n");
    printf("\n");

    r = cli_sethookfunc(cli_hook_func, NULL);
    ubi_assert(r == 0);

    r = cli_sethelphookfunc(cli_help_hook_func);
    ubi_assert(r == 0);

    r = cli_setprompt("dfsdm_audiorecord> ");
    ubi_assert(r == 0);

    r = task_create(NULL, cli_main, NULL, task_getmiddlepriority(), 0, "cli_main");
    ubi_assert(r == 0);

    /* Initialize DFSDM channels and filter for record */
    DFSDM_Init();

    /* Initialize playback */
    Playback_Init();

    /* Start DFSDM conversions */
    if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&DfsdmRightFilterHandle, RightRecBuff, 2048))
    {
        bsp_abortsystem();
    }
    if(HAL_OK != HAL_DFSDM_FilterRegularStart_DMA(&DfsdmLeftFilterHandle, LeftRecBuff, 2048))
    {
        bsp_abortsystem();
    }
  
    /* Start loopback */
    while(1)
    {
        if((DmaLeftRecHalfBuffCplt == 1) && (DmaRightRecHalfBuffCplt == 1))
        {
            /* Store values on Play buff */
            for(uint32_t i = 0; i < 1024; i++)
            {
                PlayBuff[2*i]     = SaturaLH((LeftRecBuff[i] >> 8), -32768, 32767);
                PlayBuff[(2*i)+1] = SaturaLH((RightRecBuff[i] >> 8), -32768, 32767);
            }
            if(PlaybackStarted == 0)
            {
                if(0 != audio_drv->Play(AUDIO_I2C_ADDRESS, (uint16_t *) &PlayBuff[0], 4096))
                {
                    bsp_abortsystem();
                }
                if(HAL_OK != HAL_SAI_Transmit_DMA(&SaiHandle, (uint8_t *) &PlayBuff[0], 4096))
                {
                    bsp_abortsystem();
                }
                PlaybackStarted = 1;
            }      
            DmaLeftRecHalfBuffCplt  = 0;
            DmaRightRecHalfBuffCplt = 0;
        }
        if((DmaLeftRecBuffCplt == 1) && (DmaRightRecBuffCplt == 1))
        {
            /* Store values on Play buff */
            for(uint32_t i = 1024; i < 2048; i++)
            {
                PlayBuff[2*i]     = SaturaLH((LeftRecBuff[i] >> 8), -32768, 32767);
                PlayBuff[(2*i)+1] = SaturaLH((RightRecBuff[i] >> 8), -32768, 32767);
            }
            DmaLeftRecBuffCplt  = 0;
            DmaRightRecBuffCplt = 0;
        }
        // task_sleep(1);
    }
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

static int my_command(char *str, int len, void *arg)
{
    printf("\n");
    printf("done\n");

    return 0;
}

