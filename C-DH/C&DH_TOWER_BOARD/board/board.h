/* This is a template file for board configuration created by New Kinetis SDK 2.x Project Wizard. Enjoy! */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* The board name */
#define BOARD_NAME "C&DH-MK22FN1M0VLL12"
#define CPU_MK22FN1M0VLL12

/*! @brief The UART to use for debug messages. */
#define BOARD_USE_UART
#define BOARD_DEBUG_UART_TYPE DEBUG_CONSOLE_DEVICE_TYPE_UART
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) UART0
#define BOARD_DEBUG_UART_CLKSRC kCLOCK_BusClk
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetBusClkFreq()
#define BOARD_UART_IRQ UART0_RX_TX_IRQn
#define BOARD_UART_IRQ_HANDLER UART0_RX_TX_IRQHandler
#define BOARD_SDHC_BASEADDR SDHC					//THANH ADDED 10/17/2018 BECAUSE IT WAS ON Cubesat_Dev_Code
#define BOARD_SDHC_CLKSRC kCLOCK_CoreSysClk			//THANH ADDED 9/20/2018 BECAUSE IT WAS ON Cubesat_Dev_Code
#define BOARD_SDHC_IRQ SDHC_IRQn					//THANH ADDED REMAINING SDHC STUFF 2/15/19 to get clean compile on SDHC
#define BOARD_SDHC_CD_GPIO_BASE GPIOE
#define BOARD_SDHC_CD_GPIO_PIN 24U
#define BOARD_SDHC_CD_PORT_BASE PORTE
#define BOARD_SDHC_CD_PORT_IRQ PORTE_IRQn
#define BOARD_SDHC_CD_PORT_IRQ_HANDLER PORTE_IRQHandler

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200
#endif /* BOARD_DEBUG_UART_BAUDRATE */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief initialize debug console to enable printf for this demo/example
 */
void BOARD_InitDebugConsole(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
