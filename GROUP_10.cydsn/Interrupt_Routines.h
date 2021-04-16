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
    #define SLAVE_BUFFER_SIZE   7
    
    volatile uint8_t flagPacketReady;
    volatile uint8_t flag;
    uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE];
    
    CY_ISR_PROTO(Custom_ISR_ADC);
    
    //DA SPOSTARE IN I2C
    
    #define WHO_AM_I            0xBC
    #define _5_SAMPLES_OFF      0x14 //0b00010100 
    #define _5_SAMPLES_ON_BOTH  0x17 //0b00010111
    #define _5_SAMPLES_ON_TMP   0x15 //0b00010101
    #define _5_SAMPLES_ON_LDR   0x16 //0b00010110
    #define BYTE_TO_SEND 2
#endif
/* [] END OF FILE */
