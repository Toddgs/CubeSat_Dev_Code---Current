/*
 * fsl_pit_irq.c
 *
 *  Created on: Jul 21, 2017
 *      Author: Student
 */


//defines
#define PIT_HANDLER PIT0_IRQHandler
#define PIT_IRQ_ID PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)
