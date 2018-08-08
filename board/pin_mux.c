/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

#include "fsl_common.h"
#include "fsl_port.h"

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Function Name : BOARD_InitPins */
void BOARD_InitPins(void)
{
    /* Initialize UART1 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortD);

    /* Affects PORTD_PCR8 register */
    PORT_SetPinMux(PORTD, 8u, kPORT_MuxAlt3);
    /* Affects PORTD_PCR9 register */
    PORT_SetPinMux(PORTD, 9u, kPORT_MuxAlt3);

    /* Initialize CAN0 for PORTA */
    /* Ungate PORTA clock */
    CLOCK_EnableClock(kCLOCK_PortA);

    /* Affects PORTD_PCR8 register */
    PORT_SetPinMux(PORTA, 12u, kPORT_MuxAlt2);
    /* Affects PORTD_PCR9 register */
    PORT_SetPinMux(PORTA, 13u, kPORT_MuxAlt2);

    /*configuration for SDCARD*/
    /*=================================================*/
    /*
    config.pullSelect = kPORT_PullUp;
    config.driveStrength = kPORT_HighDriveStrength;
    config.mux = kPORT_MuxAlt4;


    /* Ungate PORTE clock */
   // CLOCK_EnableClock(kCLOCK_PortE);
    /* Ungate PORTC clock */
   // CLOCK_EnableClock(kCLOCK_PortC);
/*
    PORT_SetPinConfig(PORTE, 0U, &config);
    PORT_SetPinConfig(PORTE, 1U, &config);
    PORT_SetPinConfig(PORTE, 2U, &config);
    PORT_SetPinConfig(PORTE, 3U, &config);
    PORT_SetPinConfig(PORTE, 4U, &config);
    PORT_SetPinConfig(PORTE, 5U, &config);

    config.driveStrength = 0U;
    config.mux = kPORT_MuxAsGpio;

    PORT_SetPinConfig(PORTC, 18U, &config);
    */
    /*==============================================*/
}
