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
#include "I2C_Interface.h"




int32_t sample(uint8_t AMUX) {
    
    
    AMux_1_FastSelect(AMUX);
  
    
    value_digit = ADC_DelSig_Read32();
  
    
    if(value_digit < 0) value_digit = 0;
    if(value_digit > 65535) value_digit = 65535 ;
    
    return value_digit;
}

void reset_flags(void){
    
    flag=0;
    counter=0;
    sum_PHOTO = 0;
    sum_TMP = 0;

}
    
/* [] END OF FILE */
