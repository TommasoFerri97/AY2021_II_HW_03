/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    #include "project.h"
    #include "stdio.h"
    #define AMUX_PHOTO 0
    #define AMUX_TMP 1
    #define SAMPLES 5
    #define BYTE_TO_SEND 2
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND+1
    uint8_t DataBufferPHOTO[TRANSMIT_BUFFER_SIZE];
    uint8_t DataBufferTMP[TRANSMIT_BUFFER_SIZE];
    volatile extern uint8_t flagPacketReady;
    volatile extern uint8_t flag;
    CY_ISR_PROTO(Custom_ISR_ADC);
#endif
/* [] END OF FILE */
