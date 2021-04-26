/* ========================================
 * 
 * Group 10
 *  
 * File Name: I2C_Interface.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains the code to define the Sample function and the flag reset
 *
 * ========================================
*/

/* 
 * ========================================
 *
 * include header files containing the needed functions' declations;
 *
 * ========================================
*/ 

#include "Interrupt_Routines.h"
#include "I2C_Interface.h"

/* 
 * ========================================
 *
 * sample() definition;
 *
 * ========================================
*/ 

int32_t sample(uint8_t AMUX) {
        
    AMux_1_FastSelect(AMUX); /* switch sampling channel according to AMUX*/
  
    value_digit = ADC_DelSig_Read32(); /* sample the 16 bit value */
    
    if(value_digit < 0) value_digit = 0;
    if(value_digit > 65535) value_digit = 65535 ;
    
    return value_digit; /* return the sampled value */
    
    
}

/* 
 * ========================================
 *
 * reset_flags() definition;
 *
 * ========================================
*/ 

void reset_flags(void){
    
    counter=0;
    sum_PHOTO = 0; /* reset to avoid overwrite*/
    sum_TMP = 0;

}
    
/* [] END OF FILE */
