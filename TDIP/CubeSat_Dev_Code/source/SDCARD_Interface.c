/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

// Default template includes
#include <stdio.h>
#include <board.h>
#include <clock_config.h>
#include <fsl_clock.h>
#include <fsl_sdhc.h>
#include <MK21FA12.h>
#include <pin_mux.h>
#include <stdbool.h>
#include <stdio.h>

#include "fsl_sdmmc.h"
#include "fsl_card.h"
#include "event.h"
#include "FreeRTOS.h"
#include "fsl_port.h"
#include "fsl_mpu.h"
#include "task.h"
#include "ff.h"
#include "diskio.h"

// Definitions
#define EVENT_TIMEOUT_TRANSFER_COMPLETE (1000U)
#define EVENT_TIMEOUT_CARD_DETECT (~0U)
#define DATA_BLOCK_COUNT (5U)
#define DATA_BLOCK_START (2U)
#define DATA_BUFFER_SIZE (FSL_SDMMC_DEFAULT_BLOCK_SIZE * DATA_BLOCK_COUNT)
#define SDHC_ADMA_TABLE_WORDS (8U)
#define AccessCardTask_STACK_SIZE (DATA_BUFFER_SIZE + 1000U)
#define SD_TASK_PRIORITY (configMAX_PRIORITIES - 1U)
#define BUFFER_SIZE (100U)

// Functions
void DetectCardByGpio(void);
void Delay(uint32_t milliseconds);
void SDHC_TransferCompleteCallback(SDHC_Type *base, sdhc_handle_t *handle, status_t status, void *userData);
status_t SDHC_TransferFunction(SDHC_Type *base, sdhc_transfer_t *content);
static void AccessCardTask(void *pvParameters);

// Variables
uint32_t g_sdhcAdmaTable[SDHC_ADMA_TABLE_WORDS];
sdhc_handle_t g_sdhcHandle;
static volatile uint32_t g_sdhcTransferFailedFlag = 0;
sd_card_t g_sd;
static volatile uint32_t g_sdInsertedFlag;
uint8_t g_dataWrite[DATA_BUFFER_SIZE];
uint8_t	g_dataRead[DATA_BUFFER_SIZE];
static FATFS g_fileSystem; /* File system object */
static FIL g_fileObject;   /* File object */
static uint8_t g_bufferWrite[BUFFER_SIZE]; /* Write buffer */
static uint8_t g_bufferRead[BUFFER_SIZE];  /* Read buffer */

/*!
 * @brief Application entry point.
 */
void SDCARD_Interface() {
	/* Init board hardware. */
	MPU_Enable(MPU, false);

	/* Add your code here */

	if (pdPASS !=
			xTaskCreate(AccessCardTask, "AccessCardTask", AccessCardTask_STACK_SIZE, NULL, SD_TASK_PRIORITY, NULL))
	{
		return -1;
	}

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* Scheduler should never reach this point. */
	while (true)
	{
	}

}

void DetectCardByGpio(void)
{
	if (GPIO_ReadPinInput(BOARD_SDHC_CD_GPIO_BASE, BOARD_SDHC_CD_GPIO_PIN))
#if defined BOARD_SDHC_CD_LOGIC_RISING
	{
		g_sdInsertedFlag = 1U;
	}
	else
	{
		g_sdInsertedFlag = 0U;
	}
#else
	{
		g_sdInsertedFlag = 0U;
	}
	else
	{
		g_sdInsertedFlag = 1U;
	}
#endif
}

void BOARD_SDHC_CD_PORT_IRQ_HANDLER(void)
{
	if (PORT_GetPinsInterruptFlags(BOARD_SDHC_CD_PORT_BASE) == (1U << BOARD_SDHC_CD_GPIO_PIN))
	{
		DetectCardByGpio();
	}
	/* Clear interrupt flag.*/
	PORT_ClearPinsInterruptFlags(BOARD_SDHC_CD_PORT_BASE, ~0U);
	EVENT_Notify(kEVENT_CardDetect);
}

void Delay(uint32_t milliseconds)
{
	uint32_t i;
	uint32_t j;

	for (i = 0; i < milliseconds; i++)
	{
		for (j = 0; j < 20000U; j++)
		{
			__asm("NOP");
		}
	}
}

void SDHC_TransferCompleteCallback(SDHC_Type *base, sdhc_handle_t *handle, status_t status, void *userData)
{
	if (status == kStatus_Success)
	{
		g_sdhcTransferFailedFlag = 0;
	}
	else
	{
		g_sdhcTransferFailedFlag = 1;
	}

	EVENT_Notify(kEVENT_TransferComplete);
}

status_t SDHC_TransferFunction(SDHC_Type *base, sdhc_transfer_t *content)
{
	status_t error = kStatus_Success;

	do
	{
		error = SDHC_TransferNonBlocking(base, &g_sdhcHandle, g_sdhcAdmaTable, SDHC_ADMA_TABLE_WORDS, content);
	} while (error == kStatus_SDHC_BusyTransferring);

	if ((error != kStatus_Success) || (false == EVENT_Wait(kEVENT_TransferComplete, EVENT_TIMEOUT_TRANSFER_COMPLETE)) || (g_sdhcTransferFailedFlag))
	{
		error = kStatus_Fail;
	}

	return error;
}

// Modifying AccessCardTask to initialize the FatFS file system. - NS
static void AccessCardTask(void *pvParameters)
{
	// File system code - NS
	FRESULT error;
	DIR directory; /* Directory object */
	FILINFO fileInformation;
	UINT bytesWritten;
	UINT bytesRead;
	const TCHAR driverNumberBuffer[3U] = {SDDISK + '0', ':', '/'};

	// Original function code - NS
	sd_card_t *card = &g_sd;
	sdhc_config_t *sdhcConfig = &(g_sd.host.config);
	sdhc_transfer_callback_t sdhcCallback = {0};
	bool isReadOnly;
	bool failedFlag = false;
	char ch = '0';

	if (!EVENT_Create(kEVENT_CardDetect))
	{
		return;
	}

	/* Card detection pin will generate interrupt on either edge */
	PORT_SetPinInterruptConfig(BOARD_SDHC_CD_PORT_BASE, BOARD_SDHC_CD_GPIO_PIN, kPORT_InterruptEitherEdge);
	/* Open card detection pin NVIC. */
	NVIC_EnableIRQ(BOARD_SDHC_CD_PORT_IRQ);
	NVIC_SetPriority(BOARD_SDHC_CD_PORT_IRQ, 5U);
	NVIC_SetPriority(BOARD_SDHC_IRQ, 5U);

	DetectCardByGpio();
	printf("\r\nPlease insert a card into board.\r\n");
	if (!g_sdInsertedFlag)
	{
		/* Wait card inserted. */
		do
		{
			if (!EVENT_Wait(kEVENT_CardDetect, EVENT_TIMEOUT_CARD_DETECT))
			{
				return;
			}
		} while (!g_sdInsertedFlag);
	}
	printf("Detected SD card inserted.\r\n");
	/* Delay some time to make card stable. */
	Delay(1000U);

	/* Initialize SDHC. */
	sdhcConfig->cardDetectDat3 = false;
	sdhcConfig->endianMode = kSDHC_EndianModeLittle;
	sdhcConfig->dmaMode = kSDHC_DmaModeAdma2;
	sdhcConfig->readWatermarkLevel = 0x80U;
	sdhcConfig->writeWatermarkLevel = 0x80U;
	SDHC_Init(BOARD_SDHC_BASEADDR, sdhcConfig);

	/* Set callback for SDHC driver. */
	sdhcCallback.TransferComplete = SDHC_TransferCompleteCallback;
	/* Create handle for SDHC driver */
	SDHC_TransferCreateHandle(BOARD_SDHC_BASEADDR, &g_sdhcHandle, &sdhcCallback, NULL);

	/* Create transfer complete event. */
	if (false == EVENT_Create(kEVENT_TransferComplete))
	{
		return;
	}

	/* Fill state in card driver. */
	card->host.base = BOARD_SDHC_BASEADDR;
	card->host.sourceClock_Hz = CLOCK_GetFreq(BOARD_SDHC_CLKSRC);
	card->host.transfer = SDHC_TransferFunction;

	/* Init card. */
	printf("\r\nInitializing card.\r\n");
	if (SD_Init(card))
	{
		printf("\r\nSD card init failed.\r\n");
		return;
	}

	printf("\r\nChecking read only.\r\n");
	isReadOnly = SD_CheckReadOnly(card);
	if (isReadOnly){
		printf("Error: card is read only.");
		return;
	}

	// Mount file system - NS
	printf("Mounting file system");
	if (f_mount(&g_fileSystem, driverNumberBuffer, 0U))
	{
		printf("Mount volume failed.\r\n");
		return -1;
	}

	#if (_FS_RPATH >= 2U)
		error = f_chdrive((char const *)&driverNumberBuffer[0U]);
		if (error)
		{
			printf("Change drive failed.\r\n");
			return -1;
		}
	#endif

	printf("\r\nCreating text file\r\n");
	error = f_open(&g_fileObject, _T("calendar.txt"), (FA_WRITE | FA_READ | FA_CREATE_ALWAYS));
	if (error)
	    {
	        if (error == FR_EXIST)
	        {
	            printf("File exists.\r\n");
	        }
	        else
	        {
	            printf("Open file failed.\r\n");
	            return -1;
	        }
	    }

	memset(g_bufferWrite, 'z', sizeof(g_bufferWrite));
	g_bufferWrite[BUFFER_SIZE - 2U] = '\r';
	g_bufferWrite[BUFFER_SIZE - 1U] = '\n';

	printf("\r\nWrite/read file until encounters error......\r\n");
	    while (true)
	    {
	        if (failedFlag || (ch == 'q'))
	        {
	            break;
	        }

	        printf("\r\nWrite to above created file.\r\n");
	        error = f_write(&g_fileObject, g_bufferWrite, sizeof(g_bufferWrite), &bytesWritten);
	        if ((error) || (bytesWritten != sizeof(g_bufferWrite)))
	        {
	            printf("Write file failed. \r\n");
	            failedFlag = true;
	            continue;
	        }

	        /* Move the file pointer */
	        if (f_lseek(&g_fileObject, 0U))
	        {
	            printf("Set file pointer position failed. \r\n");
	            failedFlag = true;
	            continue;
	        }

	        printf("Read from above created file.\r\n");
	        memset(g_bufferRead, 0U, sizeof(g_bufferRead));
	        error = f_read(&g_fileObject, g_bufferRead, sizeof(g_bufferRead), &bytesRead);
	        if ((error) || (bytesRead != sizeof(g_bufferRead)))
	        {
	            printf("Read file failed. \r\n");
	            failedFlag = true;
	            continue;
	        }

	        printf("Compare the read/write content......\r\n");
	        if (memcmp(g_bufferWrite, g_bufferRead, sizeof(g_bufferWrite)))
	        {
	            printf("Compare read/write content isn't consistent.\r\n");
	            failedFlag = true;
	            continue;
	        }
	        printf("The read/write content is consistent.\r\n");

	        printf("\r\nInput 'q' to quit read/write.\r\nInput other char to read/write file again.\r\n");
	        ch = getchar();
	        putchar(ch);
	    }
	    printf("\r\nThe example will not read/write file again.\r\n");

	    if (f_close(&g_fileObject))
	    {
	        printf("\r\nClose file failed.\r\n");
	        return -1;
	    }


	SD_Deinit(card);

	vTaskSuspend(NULL);
}
