/* ========================================
 * 
 * Group 10
 *  
 * File Name: Interrupt_Routines.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains declarations of all the created ISR functions.
 *
 * ========================================
*/

#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    
    #include "project.h" /*give access to my functions all the generated header files*/
    #include "stdio.h"
    
    /* definition of ON and OFF conditions for LED*/
    
    #define LED_OFF          0
    #define LED_ON           1
    
    /* definition of PHOTO and TMP channels for MUX */
    
    #define AMUX_PHOTO       1
    #define AMUX_TMP         0
    
    /* definition of a mask used to read status bits and N_samples to average*/
    
    #define MASK             0b00000011
    #define MASK_SAMPLES     0b00001111
        
    /*
    set up of  global variables;
    volatile: volatile tells the compiler that the variable value may be modified by some external event;
    */
 
    volatile uint8_t counter;
    volatile uint8_t status,previous_status;
    volatile uint8_t N_samples,previous_N_samples;
    volatile uint8_t period,previous_period;
    
    
    CY_ISR_PROTO(Custom_ISR_ADC); /* CY_ISR_PROTO used to declare the function Custom_ISR_ADC */

#endif
/* [] END OF FILE */
