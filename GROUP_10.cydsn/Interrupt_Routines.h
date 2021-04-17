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
    
    #define LED_OFF          0
    #define LED_ON           1
    #define AMUX_PHOTO       0
    #define AMUX_TMP         1
    #define PACKET_READY     5
    #define ITS_TIME_TO_SEND 10 // IF PERIOD 2MS
    
    //volatile uint8_t flagPacketReady;
    volatile uint8_t flag;
    volatile uint8_t counter;
    volatile uint8_t status;
    
    CY_ISR_PROTO(Custom_ISR_ADC);
    

#endif
/* [] END OF FILE */
