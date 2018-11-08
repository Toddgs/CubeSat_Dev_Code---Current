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

int key = 0;

int Queue_Length = 10;

cs_event recv_event;
int pit_task_counter = 0;


static void sender_task(void*p)
{
	for(;;)
	{
		printf("sender_task - Running         \n\r");
		//Delay a task for a given number of ticks. The actual time that the task remains blocked depends on the tick rate. 
		vTaskDelay(500);
		printf("sender_task - sending         \n\r");
		printf("sender_task - sleep         \n\r");
		
		//pdTrue sets task notification value to 0. portMax_DELAY will cause the task to wait indefinitely 
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	}
}

//The following code must have been taken from the imported code, but why??? and why is it commented out?
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

		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		printf("receiver_task - running       \n\r");

		recv_event.timestamp = -1;

		xQueueReceive(Global_Queue_Handle, &recv_event, 0);

		printf("Pulled event from queue.  Message source:%d\n\r", recv_event.sourcedest);

		if(recv_event.sourcedest == FROM_CAN){
			printf("Word1:0x%08x\n\r",recv_event.canframe.dataWord0);
			printf("Word1:0x%08x\n\r",recv_event.canframe.dataWord1);
		}
	}
}


static void PIT_task(void*p)
{
	uint32_t ulNotificationValue;
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
	for(;;)
	{
		printf("\r\n PIT_task - 1");

		xHandle = xTaskGetCurrentTaskHandle();

		printf("\r\n PIT_task - putting itself to sleep now\r\n");

		ulNotificationValue = ulTaskNotifyTake( pdFALSE, portMAX_DELAY );

		if( ulNotificationValue == 1 )
		   {
		        printf("The transmission ended as expected.");
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

	vTaskStartScheduler();


//FIXME: Commented out switch statement that can be used when we get the CAN code running.
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
