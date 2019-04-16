/*
 * CAN.c
 *
 *  Created on: Nov 28, 2017
 *      Author: Student
 */


#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "fsl_pit.h"
#include "fsl_pit_irq.c"
#include "fsl_flexcan_irq.c"
#include "cubesat.h"



#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"

#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"

extern TaskHandle_t xHandle;
extern TaskHandle_t xTask1;
extern TaskHandle_t xTask2;
extern xQueueHandle Global_Queue_Handle;

//volatile bool pitIsrFlag = false;

int can_rx_counter = 0;
//BaseType_t xHigherPriorityTaskWoken = pdFALSE; //FIXME: Why is this commented out?
BaseType_t xHigherPriorityTaskWoken1 = pdFALSE;

cs_event can_rx_event;
uint32_t RxFlags;
flexcan_rx_mb_config_t mbConfig;
flexcan_frame_t RecvFrame;



void FLEXCAN_RX_HANDLER(void)
{
    /* Clear interrupt flag.*/
	//FLEXCAN_ClearStatusFlags(CAN0, kFLEXCAN_RxFifoFrameAvlFlag);//kFLEXCAN_RxFifoFrameAvlFlag);// kFLEXCAN_RxErrorWarningFlag);
	FLEXCAN_ClearMbStatusFlags(CAN0, 1 << 15);

/*    if(xHandle != NULL)
    		{
    			printf("\r\n xHandle != NULL");
    		}*/
  	//printf("\n %d\n");
  	//printf("%08x",xHandle);

    //configASSERT( xHandle != NULL );
    printf("\r\n CAN_RX_HANDLER - Channel No.0 interrupt is occured ! %d\r\n",can_rx_counter++);

    if (can_rx_counter>3){
    	while(1!=1){} //FIXME What the hell is this even for??? 
    }

   // printf("%08x",xHandle);

    //pit_event.timestamp = pit_counter;
    ReceiveCANMesg(&(can_rx_event.canframe)); //Receives the data from the CAN buffer.
    can_rx_event.sourcedest = FROM_CAN; //FIXME setting this value equal to 1???

    xQueueSendFromISR(Global_Queue_Handle, &can_rx_event, &xHigherPriorityTaskWoken1); //FIXME What does this do?
    printf("... added CAN event to queue... ");

    //WHERE IT STOPS=====================================
    // xHandle +1 therefore unblocked
    vTaskNotifyGiveFromISR( xTask2, &xHigherPriorityTaskWoken1);
    //======================================================

    //printf(" xHigerPriorityTaskWoken:");
    //printf("pointer:%08x",&xHigherPriorityTaskWoken);
    //printf(" value:%08x\r\n",xHigherPriorityTaskWoken);


    /* timer reset so no tasks to notify. */
    //xHandle = NULL;
    printf("\r\n CAN_RX_HANDLER - Channel No.0 wake up sent !\r\n");
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken1 );
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

int can_tx_counter = 0;
//BaseType_t xHigherPriorityTaskWoken = pdFALSE;
BaseType_t xHigherPriorityTaskWoken2 = pdFALSE;
cs_event can_tx_event;

void FLEXCAN_TX_HANDLER(void)
{



    /* Clear interrupt flag.*/
FLEXCAN_ClearStatusFlags(CAN0, kFLEXCAN_TxWarningInterruptEnable);
/*    if(xHandle != NULL)
    		{
    			printf("\r\n xHandle != NULL");
    		}*/
  	//printf("\n %d\n");
  	//printf("%08x",xHandle);

    //configASSERT( xHandle != NULL );
    printf("\r\n CAN_TX_HANDLER - Channel No.0 interrupt is occured ! %d\r\n",can_tx_counter++);

    if (can_tx_counter>3){
    	while(1!=1){}
    }

   // printf("%08x",xHandle);
	//prepares the transmit frame for sending data.
	printf("\n\rSending CAN data:");
	can_tx_event.canframe.format = kFLEXCAN_FrameFormatStandard;
	can_tx_event.canframe.type   = kFLEXCAN_FrameTypeData;
	can_tx_event.canframe.id     = FLEXCAN_ID_STD(0x123);
	can_tx_event.canframe.length = 8;
	can_tx_event.canframe.dataWord0 = CAN_WORD0_DATA_BYTE_0('A')|
			CAN_WORD0_DATA_BYTE_1('B')|
			CAN_WORD0_DATA_BYTE_2('B')|
			CAN_WORD0_DATA_BYTE_3('D');
	can_tx_event.canframe.dataWord1 = CAN_WORD1_DATA_BYTE_4('E')|
			CAN_WORD1_DATA_BYTE_5('F')|
			CAN_WORD1_DATA_BYTE_6('G')|
			CAN_WORD1_DATA_BYTE_7('H');


    //pit_event.timestamp = pit_counter;
    Transmit(&(can_tx_event.canframe));
    xQueueSendFromISR(Global_Queue_Handle, &can_tx_event, &xHigherPriorityTaskWoken2);
    printf("... added event to queue... ");

    //WHERE IT STOPS=====================================
    // xHandle +1 therefore unblocked
    vTaskNotifyGiveFromISR( xTask1, &xHigherPriorityTaskWoken2);
    //======================================================

    //printf(" xHigerPriorityTaskWoken:");
    //printf("pointer:%08x",&xHigherPriorityTaskWoken);
    //printf(" value:%08x\r\n",xHigherPriorityTaskWoken);


    /* timer reset so no tasks to notify. */
    //xHandle = NULL;
    printf("\r\n CAN_TX_HANDLER - Channel No.0 wake up sent !\r\n");
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken2 );
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

// This needs to grow up into a real table of buffers, message IDs, types, etc.


void FLEXCAN_INIT(void)
{
	uint8_t TX_MESSAGE_BUFFER_INDEX = 13;
	uint8_t RX_RTR_REQUEST = 14;
	uint8_t TX_RTR_REQUEST = 16;
	uint8_t RX_MESSAGE_BUFFER_INDEX = 15;

	char CanDataIn[9];
	uint32_t MESSAGE_MASK =  1<<RX_MESSAGE_BUFFER_INDEX ;

	/* Structure of initialize can */
	flexcan_config_t flexcanConfig;
	//flexcanConfig.enableRunInDebug = true;

	printf("\n\rInitializing CAN...");

	FLEXCAN_GetDefaultConfig(&flexcanConfig);
	flexcanConfig.baudRate = 115200;
	/* Init CAN module */
	FLEXCAN_Init(CAN0, &flexcanConfig, 8000000UL);


	/* Enable CAN interrupts for channel 0 */
	FLEXCAN_EnableInterrupts(CAN0, CAN0_ORed_Message_buffer_IRQn);//CAN0_ORed_Message_buffer_IRQn); //kFLEXCAN_RxWarningInterruptEnable);
	//FLEXCAN_EnableInterrupts(CAN0, kFLEXCAN_TxWarningInterruptEnable);

	//Flexcan message buffer interrupts
	FLEXCAN_EnableMbInterrupts(CAN0, MESSAGE_MASK);


	/* Enable at the NVIC */
	//EnableIRQ(CAN_TX_IRQ_ID);
	EnableIRQ(CAN_RX_IRQ_ID);
	/* Start channel 0 */


	//Enable FlexCAN module.
	FLEXCAN_Enable(CAN0, true);


	printf("\n\rSetting up receive message buffer.");

	// Sets up the receive message buffer.

	// First look for ordinary messages
	mbConfig.format    = kFLEXCAN_FrameFormatStandard;
	mbConfig.type      = kFLEXCAN_FrameTypeData;
	mbConfig.id        = FLEXCAN_ID_STD(0x123);

	FLEXCAN_SetRxMbConfig(CAN0, RX_MESSAGE_BUFFER_INDEX, &mbConfig, true);

	// Second look for RTR messages
	//mbConfig.format    = kFLEXCAN_FrameFormatStandard;
	//mbConfig.type      = kFLEXCAN_FrameTypeRemote;
	//mbConfig.id        = FLEXCAN_ID_STD(0x124);

	//FLEXCAN_SetRxMbConfig(CAN0, RX_RTR_REQUEST, &mbConfig, true);

	printf("\n\rSearching for message:\n\r");

	//Receive(&RecvFrame);

}
