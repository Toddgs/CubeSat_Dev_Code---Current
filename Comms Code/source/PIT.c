/*
 * PIT.c
 *
 *  Created on: Jul 18, 2017
 *      Author: Student
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_pit.h"
#include "fsl_pit_irq.c"
#include "cubesat.h"



#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include <FreeRTOS.h>
#include "task.h"
#include "PIT.h"
#include "queue.h"

extern TaskHandle_t xHandle;
extern TaskHandle_t xTask1;
extern TaskHandle_t xTask2;
extern xQueueHandle Global_Queue_Handle;

//volatile bool pitIsrFlag = false;

int pit_counter = 0;
//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
cs_event pit_event;

void PIT_HANDLER(void)
{



    /* Clear interrupt flag.*/
PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
/*    if(xHandle != NULL)
    		{
    			printf("\r\n xHandle != NULL");
    		}*/
  	//printf("\n %d\n");
  	//printf("%08x",xHandle);

    //configASSERT( xHandle != NULL );
    printf("\r\n PIT_HANDLER - Channel No.0 interrupt is occured ! %d\r\n",pit_counter++);
    PrintCanStatus();

    if (pit_counter>3){
    	while(1!=1){}
    }

   // printf("%08x",xHandle);

    //pit_event.timestamp = pit_counter;
    //Receive(&(pit_event.canframe));
    pit_event.sourcedest = FROM_PIT;

    xQueueSendFromISR(Global_Queue_Handle, &pit_event, &xHigherPriorityTaskWoken);
    printf("... added event to queue... ");

    //WHERE IT STOPS=====================================
    // xHandle +1 therefore unblocked
    vTaskNotifyGiveFromISR( xTask2, &xHigherPriorityTaskWoken);
    //======================================================

    //printf(" xHigerPriorityTaskWoken:");
    //printf("pointer:%08x",&xHigherPriorityTaskWoken);
    //printf(" value:%08x\r\n",xHigherPriorityTaskWoken);


    /* timer reset so no tasks to notify. */
    //xHandle = NULL;
    printf("\r\n PIT_HANDLER - Channel No.0 wake up sent !\r\n");
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    //xHandle = NULL;

    //portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    //xTaskNotifyGive(xHandle);
    //xTaskResumeFromISR(xHandle);
   /* xYielldRequired = xTaskResumeFromISR(xHandle);
    if(xYielldRequired == pdTRUE)
    {
    	kPIT_Chnl_0YIELD_FROM_ISR();
    }*/
    //xTaskNotifyGive(xHandle);
    //pitIsrFlag = true;
}

void PIT_INIT(void)
{
	/* Structure of initialize PIT */
	pit_config_t pitConfig;
	pitConfig.enableRunInDebug = true;

	PIT_GetDefaultConfig(&pitConfig);

	/* Init pit module */
	PIT_Init(PIT, &pitConfig);

	/* Set timer period for channel 0 */
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK));

	/* Enable timer interrupts for channel 0 */
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

	/* Enable at the NVIC */
	EnableIRQ(PIT_IRQ_ID);

	/* Start channel 0 */
	PRINTF("\r\nStarting PIT Timer\n\r");
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}

/*void PIT0_DVR_InstallCallback()
{

	 PRINTF("\r\n Channel No.0 interrupt is occured !");
	 pitIsrFlag = false;
}*/
