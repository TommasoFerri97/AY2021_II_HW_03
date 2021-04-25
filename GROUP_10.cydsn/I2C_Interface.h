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
#ifndef __I2C_INTERFACE_H
    #define __I2C_INTERFACE_H
    #include "project.h"
    #include "Interrupt_Routines.h"
     

    #define SLAVE_BUFFER_SIZE   7
    #define BUFFER_RW_AREA_SIZE 2
  
    
    #define ms_to_count         2
    
    volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE];

    #define WHO_AM_I            0xBC   
    
    #define STATUS_OFF          0x00
    #define STATUS_ON_BOTH      0x03 //0b00000011
    #define STATUS_ON_TMP       0x01 //0b00000001          
    #define STATUS_ON_PHOTO     0x02 //0b00000010
   
  
    int32 value_digit;
    int32 sum_PHOTO,sum_TMP; 
    
    int32_t sample (uint8_t AMUX);
    void reset_flags(void);
    
#endif
/* [] END OF FILE */
