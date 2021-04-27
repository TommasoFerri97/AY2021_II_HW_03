/* ========================================
 * 
 * Group 10
 *  
 * File Name: I2C_Interface.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains declarations of constants ,sample() and reset_flags()
 *
 * ========================================
*/
#ifndef __I2C_INTERFACE_H
    #define __I2C_INTERFACE_H
    
    #include "project.h" /*give access to my functions all the generated header files*/
    #include "Interrupt_Routines.h"
     
    /* definition of SlaveBuffer and related constants */
    
    #define SLAVE_BUFFER_SIZE   7
    #define BUFFER_RW_AREA_SIZE 2 
    volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE];
    
    /* convertion factor for timer period */
    
    #define ms_to_count         2
    
    /* WHO_AM_I register value */

    #define WHO_AM_I            0xBC   
   
    /* definition of status conditions */
    
    #define STATUS_OFF          0x00
    #define STATUS_ON_BOTH      0x03 //0b00000011
    #define STATUS_ON_TMP       0x01 //0b00000001          
    #define STATUS_ON_PHOTO     0x02 //0b00000010
   
    /* definition of variables used to compute and read the output of functions */
    
    int32 value_digit;
    int32 sum_PHOTO,sum_TMP; 
    
    /* declaration of sample() and reset_flags() */
    
    int32_t sample (uint8_t AMUX);
    void reset_flags(void);
    
#endif
/* [] END OF FILE */
