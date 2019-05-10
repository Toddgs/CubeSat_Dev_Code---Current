/*
 * Transmit&Receive.c
 *
 *  Created on: Jun 13, 2017
 *      Author: Student
 */
#include "fsl_flexcan.h"
#include "fsl_port.h"
#include "fsl_rtc.h"
#include "stdio.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "fsl_common.h"

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"


	flexcan_config_t flexcanConfig;
	flexcan_frame_t txFrame, rxFrame;
	flexcan_rx_mb_config_t mbConfig;

	rtc_config_t RTC_Config;

	/*____________________________________________________________________________________*/
	//	printf("Generating table of IDs");
		// This needs to grow up into a real table of buffers, message IDs, types, etc.
		uint8_t TX_MESSAGE_BUFFER_INDEX = 13;
		uint8_t RX_RTR_REQUEST = 14;
		uint8_t TX_RTR_REQUEST = 16;
		uint8_t RX_MESSAGE_BUFFER_INDEX = 15;
		//uint32_t TX_MASK_BUFFER_INDEX
	/*____________________________________________________________________________________*/
		//uint32_t MESSAGE_MASK =  1<<RX_MESSAGE_BUFFER_INDEX | 1<<RX_RTR_REQUEST ;
		uint32_t RxFlags;

void Board_Init()
{
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();

	uint32_t retval=0;

	/* Add your code here */

	//Initialize FlexCAN module.
	FLEXCAN_GetDefaultConfig(&flexcanConfig);
	FLEXCAN_Init(CAN0, &flexcanConfig, 8000000UL);

	//Initialize RTC
	RTC_GetDefaultConfig(&RTC_Config);
	RTC_Init(RTC,&RTC_Config);
	EnableIRQ(RTC_Seconds_IRQn);

	//Enable FlexCAN module.
	FLEXCAN_Enable(CAN0, true);

/*____________________________________________________________________________________*/
	printf("\n\rGenerating table of IDs");
	// This needs to grow up into a real table of buffers, message IDs, types, etc.
	uint8_t TX_MESSAGE_BUFFER_INDEX = 13;
	uint8_t RX_RTR_REQUEST = 14;
	uint8_t TX_RTR_REQUEST = 16;
	uint8_t RX_MESSAGE_BUFFER_INDEX = 15;
	//uint32_t TX_MASK_BUFFER_INDEX
/*____________________________________________________________________________________*/
	uint32_t MESSAGE_MASK =  1<<RX_MESSAGE_BUFFER_INDEX | 1<<RX_RTR_REQUEST ;
	uint32_t RxFlags;
}

void Transmit()
{
	int retval;
	FLEXCAN_SetTxMbConfig(CAN0, 13, true);

	//prepares the transmit frame for sending data.
	printf("\n\rSending CAN data:");
	txFrame.format = kFLEXCAN_FrameFormatStandard;
	txFrame.type   = kFLEXCAN_FrameTypeData;
	txFrame.id     = FLEXCAN_ID_STD(0x123);
	txFrame.length = 8;
	txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0('A')|
			CAN_WORD0_DATA_BYTE_1('B')|
			CAN_WORD0_DATA_BYTE_2('B')|
			CAN_WORD0_DATA_BYTE_3('D');
	txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4('E')|
			CAN_WORD1_DATA_BYTE_5('F')|
			CAN_WORD1_DATA_BYTE_6('G')|
			CAN_WORD1_DATA_BYTE_7('H');

	//retval = FLEXCAN_GetStatusFlags(CAN0);
	//printf("\n\rESR1: < 0x%08lx >\n\r",CAN0->ESR1);

	//Writes a transmit message buffer to send a CAN Message.
	FLEXCAN_WriteTxMb(CAN0,TX_MESSAGE_BUFFER_INDEX,&txFrame);

	retval = FLEXCAN_GetStatusFlags(CAN0);
	printf("\n\rESR1: < 0x%08lx >\n\r",CAN0->ESR1);

	//waits until the transmit message buffer is empty.
	while(!FLEXCAN_GetMbStatusFlags(CAN0,  1 << TX_MESSAGE_BUFFER_INDEX));

	//Cleans the transmit message buffer empty status.
	FLEXCAN_ClearMbStatusFlags(CAN0, 1 << TX_MESSAGE_BUFFER_INDEX);
}


void Receive()
{
	char CanDataIn[9];
	uint32_t MESSAGE_MASK =  1<<RX_MESSAGE_BUFFER_INDEX | 1<<RX_RTR_REQUEST ;
	  printf("\n\rSetting up receive message buffer.");

	  // Sets up the receive message buffer.

	  // First look for ordinary messages
	  mbConfig.format    = kFLEXCAN_FrameFormatStandard;
	  mbConfig.type      = kFLEXCAN_FrameTypeData;
	  mbConfig.id        = FLEXCAN_ID_STD(0x123);

	  FLEXCAN_SetRxMbConfig(CAN0, RX_MESSAGE_BUFFER_INDEX, &mbConfig, true);

	  // Second look for RTR messages
	  mbConfig.format    = kFLEXCAN_FrameFormatStandard;
	  mbConfig.type      = kFLEXCAN_FrameTypeRemote;
	  mbConfig.id        = FLEXCAN_ID_STD(0x124);

	  FLEXCAN_SetRxMbConfig(CAN0, RX_RTR_REQUEST, &mbConfig, true);

	  printf("\n\rSearching for message:\n\r");

	  while (1==1)
	   { //loop to check for messages...



	 	  // Waits until the receive message buffer is full.
	 	  while (!FLEXCAN_GetMbStatusFlags(CAN0, MESSAGE_MASK));
	 	  printf("\n\rMessage received.");
	 	  RxFlags = FLEXCAN_GetMbStatusFlags(CAN0, MESSAGE_MASK);
	 	  printf("\n\rRXFlag: < %08lx >\n\r",RxFlags);

	 	  if ( RxFlags & (1<<RX_MESSAGE_BUFFER_INDEX) )
	 	  {

	 		// Reads the received message from the receive message buffer.
	 		FLEXCAN_ReadRxMb(CAN0, RX_MESSAGE_BUFFER_INDEX, &rxFrame);
	 		printf("\n\rRX_MESSAGE_BUFFER_INDEX: < %d > ",RX_MESSAGE_BUFFER_INDEX);



	 		// Cleans the receive message buffer full status.
	 		FLEXCAN_ClearMbStatusFlags(CAN0, 1 << RX_MESSAGE_BUFFER_INDEX);
	 		printf("\n\rCleaning buffer.");
	 		printf("\n\rFrame length: < %d >",rxFrame.length);

	 		ReadCanData(&rxFrame,CanDataIn);
	 		printf("\n\rCanDataIn: ->%s<-",CanDataIn);
	 		break;
	 	  }

	 	 if ( RxFlags & (1<<RX_RTR_REQUEST) )
	 	 	  {
	 		 	 printf("\n\rResponding to RTR Request\n\r");
	 	 		//Reads the received message from the receive message buffer.
	 	 		FLEXCAN_ReadRxMb(CAN0, RX_RTR_REQUEST, &rxFrame);
	 	 		printf("\n\rRX_RTR_REQUEST: < %d >",RX_RTR_REQUEST);



	 	 		// Cleans the receive message buffer full status.
	 	 		FLEXCAN_ClearMbStatusFlags(CAN0, 1 << RX_RTR_REQUEST);
	 	 		printf("\n\rCleaning buffer.");

	 	 		ReadCanData(&rxFrame,CanDataIn);
	 	 		printf("\n\rCanDataIn: ->%s<-\n\r",CanDataIn);

	 	 		Transmit();
	 	 		break;
	 	 }
	   }


}


void Transmit_RTR()
{
	int retval;
	FLEXCAN_SetTxMbConfig(CAN0, TX_MESSAGE_BUFFER_INDEX, true);

				printf("\n sending an RTR Request\n\r1...");
				//prepares the transmit frame for sending data.
				txFrame.format = kFLEXCAN_FrameFormatStandard;
				txFrame.type   = kFLEXCAN_FrameTypeRemote;
				txFrame.id     = FLEXCAN_ID_STD(0x124);
				txFrame.length = 0;
				txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0('P')|
						CAN_WORD0_DATA_BYTE_1('Q')|
						CAN_WORD0_DATA_BYTE_2('R')|
						CAN_WORD0_DATA_BYTE_3('S');
				txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4('t')|
						CAN_WORD1_DATA_BYTE_5('u')|
						CAN_WORD1_DATA_BYTE_6('v')|
						CAN_WORD1_DATA_BYTE_7('W');
				printf("1.5...");


				printf("2...");

				retval = FLEXCAN_GetStatusFlags(CAN0);
				printf("ESR: 0x%08lx\n\r",CAN0->ESR1);

				//Writes a transmit message buffer to send a CAN Message.
				FLEXCAN_WriteTxMb(CAN0,TX_MESSAGE_BUFFER_INDEX,&txFrame);
				printf("3...");

				retval = FLEXCAN_GetStatusFlags(CAN0);
				printf("ESR: 0x%08lx\n\r",CAN0->ESR1);

				//waits until the transmit message buffer is empty.
				while(!FLEXCAN_GetMbStatusFlags(CAN0,  1 << TX_MESSAGE_BUFFER_INDEX));
				printf("4...\n\r");

				//Cleans the transmit message buffer empty status.
				FLEXCAN_ClearMbStatusFlags(CAN0, 1 << TX_MESSAGE_BUFFER_INDEX);

				Receive();

}


void ReadCanData(flexcan_frame_t *inFrame, char *Array) {
	int i;
	char *Outptr, *Inptr;
	int j;

	j = inFrame->length;

	Array[0] = inFrame->dataByte0;
	Array[1] = inFrame->dataByte1;
	Array[2] = inFrame->dataByte2;
	Array[3] = inFrame->dataByte3;
	Array[4] = inFrame->dataByte4;
	Array[5] = inFrame->dataByte5;
	Array[6] = inFrame->dataByte6;
	Array[7] = inFrame->dataByte7;

	Array[j] = NULL;
}
