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
#include "Interrupt_Routines.h"
#include "I2C_interface.h"

void turn_off (){

    ADC_DelSig_StopConvert();   //fermo campionamento

    flag = 0;                   //resetto flag di conteggio byte
    counter = 0;                //resetto flag di conteggio tempo
    LED_Write(LED_OFF);         //spengo led
    
    // PHOTO and TMP Array non resettati, tanto verranno sovrascritti
}
void turn_on (){

    ADC_DelSig_StartConvert();   //fermo campionamento

    flag = 0;                    //resetto flag di conteggio byte
    counter = 0;                 //resetto flag di conteggio tempo

    
    // PHOTO and TMP Array non resettati, tanto verranno sovrascritti
}

uint32_t sample(uint8_t AMUX) {
    
    ADC_DelSig_AMux_Select(AMUX); 
    uint16_t value_digit= ADC_DelSig_Read32();
    if(value_digit < 0) value_digit = 0;
    if(value_digit > 65535) value_digit = 65535 ;
    
    return value_digit;
}
    
/* [] END OF FILE */
