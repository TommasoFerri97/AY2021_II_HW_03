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
    #define AMUX_PHOTO       1
    #define AMUX_TMP         0
    
    
    #define MASK             0b00000011
    
    //volatile uint8_t flagPacketReady;
    volatile uint8_t flag;
    volatile uint8_t counter;
    volatile uint8_t status,previous_status;
    volatile uint8_t N_samples,previous_N_samples;
    volatile uint8_t period,previous_period;
    
    
    CY_ISR_PROTO(Custom_ISR_ADC);

#endif
/* [] END OF FILE */
