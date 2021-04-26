/* ========================================
 * 
 * Group 10
 *  
 * File Name: Interrupt_Routines.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains the code to handle ISR for data acquisition and EZI2C ExitCallBack
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
#include "cyapicallbacks.h"

/* 
 * ========================================
 *
 * Custom_ISR_ADC definition;
 *
 * ========================================
*/ 

CY_ISR(Custom_ISR_ADC) /* CY_ISR used to define the function declared with CY_ISR_PROTO*/
{
    
    TIMER_ReadStatusRegister(); 
    /*Returns the current state of the status register; the interrupt output remains asserted until the status register is read */
    
    if (status != STATUS_OFF && counter < N_samples){ /* check of convertion conditions */
       
        counter++; /* counting goes on till N_samples */
        
        /* according to status sample the signals from my sensors */
            switch (status){
            
            
            case STATUS_ON_PHOTO: 
                                    {sum_PHOTO += sample(AMUX_PHOTO); 
                                    
                                    break;}
                                    
                                    
            case STATUS_ON_TMP:     
                                    {sum_TMP += sample(AMUX_TMP);
                                    
                                    break;}
                                    
            case STATUS_ON_BOTH:
                                    {sum_PHOTO += sample(AMUX_PHOTO); 
                                     sum_TMP += sample(AMUX_TMP);
                                    
                                    break;}
            default : break;
            }
        
    }
}
    
/* 
 * ========================================
 *
 * EZI2C_ISR_ExitCallback() definition;
 *
 * ========================================
*/ 

void EZI2C_ISR_ExitCallback(void) /* Everytime we get a new command from bridge control panel we run these code lines*/
    
{   
    
    /* read the status */
    
    status = (SlaveBuffer[0] & MASK); /* take only bit 0 and bit 1 of SlaveBuffer[0]*/
    
    /* read the Number of samples */ 
    
    N_samples = (SlaveBuffer[0] >> 2) & MASK_SAMPLES; /* two shifts to right to not consider status bits */
    
    /* read the period of the ISR */
    
    period = SlaveBuffer[1];
    
 
    
    /* if the period has been changed, update it */   
    
    if ( period != previous_period )    {
                                        TIMER_WritePeriod((period*ms_to_count)-1);
                                        
                                        previous_period = period;
                                        }
    
   
    
    /* if the status has been changed, update it */
    
    if ( status != previous_status )    {
                                        previous_status = status;  
                                      
                                        switch(status) {

                                        case STATUS_OFF:     {  
                                                                reset_flags();
                                                                LED_Write(LED_OFF);  
                                                                break;}
                                                                

                                        case STATUS_ON_BOTH: {  /* if we sample both signals turn on the LED */ 
                                                                reset_flags();
                                                                LED_Write(LED_ON);
                                                                break;}
                                                                
                                        case STATUS_ON_PHOTO:{  
                                                                reset_flags();
                                                                LED_Write(LED_OFF);
                                                                break;}
                                        
                                        case STATUS_ON_TMP:  {  
                                                                reset_flags();
                                                                LED_Write(LED_OFF);
                                                                break;}
                                                                
                                        
                                        default :             break;
                                          }
                                        }
    

  
}
/* [] END OF FILE */
