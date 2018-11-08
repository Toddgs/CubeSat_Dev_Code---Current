#include "fsl_flexcan.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "TransmitReceive.c"
#include "SDCARD_Interface.c"

#include <stdio.h>

/*Kernal includes*/
#include <FreeRTOS.h>
#include "task.h"
#include "queue.h"
#include "PIT.c"
#include "PIT.h"
#include "cubesat.h"
#include "CAN.c"
//PIT: Periodic Interrupt Timer

/*!
 * @brief Application entry point.
 */

/*Generating Queue*/
xQueueHandle Global_Queue_Handle = 0;

//declaring task handlers-the binary semaphore
TaskHandle_t xTask1 = NULL, xTask2 = NULL;
//static TaskHandle_t xHandle = NULL;

//eTaskState eTaskGetState(TaskHandle_t xHandle);

int key = 0;

int Queue_Length = 10;

cs_event recv_event;
int pit_task_counter = 0;


/*void PIT_HANDLER(void)
{
	//BaseType_t xYielldRequired;


     Clear interrupt flag.
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, PIT_TFLG_TIF_MASK);
    //printf("\r\n Channel No.0 interrupt is occured !");
    xTaskResumeFromISR(xHandle);
    xYielldRequired = xTaskResumeFromISR(xHandle);
    if(xYielldRequired == pdTRUE)
    {
    	kPIT_Chnl_0YIELD_FROM_ISR();
    }
    //xTaskNotifyGive(xHandle);
    //pitIsrFlag = true;
}*/


static void sender_task(void*p)
{
	for(;;)
	{
		printf("sender_task - Running         \n\r");
		//Delay a task for a given number of ticks. The actual time that the task remains blocked depends on the tick rate. 
		vTaskDelay(500);
		printf("sender_task - sending         \n\r");
		// xTask2 +1
		//xTaskNotifyGive(xTask2);
		printf("sender_task - sleep         \n\r");
		// xTask2 -1
		
		//pdTrue sets task notification value to 0. portMax_DELAY will cause the task to wait indefinitely 
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
	//////////////////////////////
/*	int i = 0;
	while(1){
//if(xTask1 != NULL){
	//ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		//vTaskResume(xTask2);
		printf("\n\rSending %i to receiver task", i);
		if (!xQueueSend(Global_Queue_Handle, &i, 1000)){
			puts("\n\rFailed to send to queue");
		}

		//++key;
		++i;
		vTaskDelay(2000);

		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		xTaskNotifyGive(xTask2);


		//vTaskResume(xTask2);
//}
	}*/

	/////////////////////////////
}

//-------------------------------------------------------------
/* This function must be defined in a C source file, not the FreeRTOSConfig.h header
file. */
/*void vAssertCalled( const char *pcFile, uint32_t ulLine )
{
  Inside this function, pcFile holds the name of the source file that contains
 the line that detected the error, and ulLine holds the line number in the source
 file. The pcFile and ulLine values can be printed out, or otherwise recorded,
 before the following infinite loop is entered.
printf( pcFile,"\n\r"  );
printf( "\n\r%i",ulLine );
  Disable interrupts so the tick interrupt stops executing, then sit in a loop
 so execution does not move past the line that failed the assertion.
 //taskDISABLE_INTERRUPTS();
 for( ;; );
}*/
/*-----------------------------------------------------------*/

static void receiver_task(void*p)
{
	for(;;)
	{
		printf("receiver_task - sleep        \n\r");
		// xTask1 -1 therefore blocked
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		printf("receiver_task - running       \n\r");

		recv_event.timestamp = -1;

		xQueueReceive(Global_Queue_Handle, &recv_event, 0);

		printf("Pulled event from queue.  Message source:%d\n\r", recv_event.sourcedest);

		if(recv_event.sourcedest == FROM_CAN){
			printf("Word1:0x%08x\n\r",recv_event.canframe.dataWord0);
			printf("Word1:0x%08x\n\r",recv_event.canframe.dataWord1);
		}


		// xTask1 +1 therefore unblocked
		//xTaskNotifyGive(xTask1);
		//xTaskNotifyGive(xTask1);
	}

	//////////////////////////////////////////////////
	/*int rx_int = 0;
	//while(key>0){
	while(1){
		//if(xTask1 != NULL){
			ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		//if(ulTaskNotifyTake(pdTRUE, portMAX_DELAY)){
		//while(key>0){
		if (xQueueReceive(Global_Queue_Handle, &rx_int, 1000)){
			printf("\n\rReceived %i", rx_int);
		}
		else{
			puts("\n\rTime elapsed without receiving data");
		}
		//--key;
		xTaskNotifyGive(xTask1);
		//}
	}*/
	////////////////////////////////////////////
}

	//vTaskSuspend(NULL);



	//}

static void PIT_task(void*p)
{
	uint32_t ulNotificationValue;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
	for(;;)
	{
		printf("\r\n PIT_task - 1");
/*		if(xHandle == NULL)
		{
			printf("\r\n xHandle == NULL");
		}*/

		//configASSERT( xHandle == NULL );

		/* Store the handle of the calling task. */
		xHandle = xTaskGetCurrentTaskHandle();
		//printf(" 1\n");
		//printf("0x%08x",xHandle);
		//configASSERT( xHandle == NULL );
		//printf(" PIT_task - %d",pit_task_counter++);



	    /* Store the handle of the calling task. */
		//xHandle = xTaskGetCurrentTaskHandle();
		printf("\r\n PIT_task - putting itself to sleep now\r\n");
		//ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
		//ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		//printf("\r\n PIT_task - Channel No.0 task is occured !");
		//xTaskNotifyGive(xHandle);
		// xHandle -1 therefore unblocked
		//taskENABLE_INTERRUPTS();
		ulNotificationValue = ulTaskNotifyTake( pdFALSE, portMAX_DELAY );
		//printf("0x%08x",ulNotificationValue);
		if( ulNotificationValue == 1 )
		   {
		        printf("The transmission ended as expected.");
		        //ulTaskNotifyTake( pdTRUE, xMaxBlockTime );
		    }
		    else
		    {
		    	  printf("The call to ulTaskNotifyTake() timed out.");
		    }
	}
}
int main(void){

	/* Init board hardware. */

	Board_Init();
	MPU_Enable(MPU, false);
	NVIC_SetPriority ( 48, 14 ); /* CAN0 is IRQ 75.  MAX priority is 5, so we need to set to
	next highest even number than 2*5, so priority = 12 */
	NVIC_SetPriority ( CAN0_ORed_Message_buffer_IRQn, 12 );

	PIT_INIT();

	FLEXCAN_INIT();
	/* Add your code here */


	/*Creating Queue*/
	Global_Queue_Handle = xQueueCreate(Queue_Length, sizeof(cs_event));

	xTaskCreate(sender_task, (signed char*) "tx", 500, NULL, tskIDLE_PRIORITY, &xTask1);
	xTaskCreate(receiver_task, (signed char*) "rx", 500, NULL, tskIDLE_PRIORITY, &xTask2);
	//xTaskCreate(PIT_task, (signed char*) "pit", 500, NULL, tskIDLE_PRIORITY, &xHandle);

	vTaskStartScheduler();



/*	char a = 0;
	while(1){
		printf("\n\rC&DH Monitor>");
		a = getchar();
		printf("%c\n\r",a);
		switch ( a )
		{

		case 'l':
			//xTaskCreate(Transmit_RTR, (signed char*) "Transmit_RTR", 1024, NULL, 1, NULL);

		case 't':
			//xTaskCreate(Transmit, (signed char*) "Transmit_RTR", 1024, NULL, 1, NULL);
			xTaskCreate(sender_task, (signed char*) "tx", 500, NULL, tskIDLE_PRIORITY, xTask1);
			break;
		case 'r':
			//xTaskCreate(Receive, (signed char*) "Transmit_RTR", 1024, NULL, 1, NULL);
			xTaskCreate(receiver_task, (signed char*) "rx", 500, NULL, tskIDLE_PRIORITY, xTask2);
			break;
		case 's':
			//xTaskCreate(SDCARD_Interface, (signed char*) "Transmit_RTR", 1024, NULL, 1, NULL);
			printf("012345678901234556789\n\r");
			break;
		case 'q':
			//xTaskCreate(hello, (signed char*) "hello", 512, NULL, 1, NULL);
			vTaskStartScheduler();
			break;
		default:
		{
			//vTaskStartScheduler();
			break;
		}
		}
	}*/






	//xTaskCreate(sender_task, (signed char*) "tx", 1024, NULL, 1, NULL);
	//xTaskCreate(receiver_task, (signed char*) "rx", 1024, NULL, 1, NULL);
	/*	if (pdPASS !=
			xTaskCreate(AccessCardTask, "AccessCardTask", AccessCardTask_STACK_SIZE, NULL, SD_TASK_PRIORITY, NULL))
	{
		return -1;
	}*/




	/* Start the tasks and timer running. */
	//vTaskStartScheduler();

	/* Scheduler should never reach this point. */
	while (true)
	{
		PrintCanStatus();
	}

	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}
