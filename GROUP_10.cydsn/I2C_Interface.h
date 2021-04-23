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
     
    
    #define SAMPLES 5
    #define SLAVE_BUFFER_SIZE   7
    #define BUFFER_RW_AREA_SIZE 2
    

    volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE];

    
    #define WHO_AM_I            0xBC
    #define _5_SAMPLES_OFF      0x14 //0b00010100 
   
    
    #define STATUS_OFF          0x00
    #define STATUS_ON_BOTH      0x03 //0b00000011
    #define STATUS_ON_TMP       0x01 //0b00000001          
    #define STATUS_ON_PHOTO     0x02 //0b00000010
   
    #define DEFAULT_PERIOD      199
    #define BYTE_TO_SEND        2

    
    uint16_t TMP_Array[SAMPLES];
    uint16_t PHOTO_Array[SAMPLES];
    int32 value_digit;
    
    volatile int32 sum_PHOTO,sum_TMP; 
    
    //funzione per fermare lo stream di dati e resettare flags
    void turn_off(void);
    void turn_on(void);
    
    //function which samples the channel AMUX
    int32_t sample (uint8_t AMUX);
    
#endif
/* [] END OF FILE */
