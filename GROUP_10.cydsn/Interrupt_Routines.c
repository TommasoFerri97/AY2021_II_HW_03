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
 * include header files containing the needed functions' declarations;
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

CY_ISR(Custom_ISR_ADC) 
{
    /*Read the status register to clear the TC bit, and allow further TC-Interrupts */
    
    TIMER_ReadStatusRegister(); 
    
    /* check of convertion conditions */
    
    if (status != STATUS_OFF && counter < N_samples){ 
        
        /* counting goes on till N_samples */
        counter++; 
        
        /* according to the status, sample the signals from the sensors */
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
    
    /* read the status : take only bit 0 and bit 1 of SlaveBuffer[0] */
    
    status = (SlaveBuffer[0] & MASK); 
    
    /* read the Number of samples :  two shifts to right to not consider status bits */ 
    
    N_samples = (SlaveBuffer[0] >> 2) & MASK_SAMPLES; 
    
    /* read the period [ms] of the ISR */
    
    period = SlaveBuffer[1];
    
    /* if the Number of samples has been changed, reset flags */ 
    if ( N_samples != previous_N_samples )    {
                                        
                                                reset_flags();
                                        
                                                previous_N_samples = N_samples;
                                        
                                                }
    
    /* if the period has been changed, update it */   
    
    if ( period != previous_period )    {
                                        TIMER_Stop();
                                        
                                        /*update period*/
                                        TIMER_WritePeriod((period*ms_to_count)-1);
                                        
                                        /*reload the counter*/
                                        TIMER_WriteCounter(0);
                                        
                                        TIMER_Start();
                                        
                                        reset_flags();
                                        
                                        previous_period = period;
                                        }
    
   
    
    /* if the status has been changed, update it */
    
    if ( status != previous_status )    {
                                        switch(status) {

                                            case STATUS_OFF:     {  LED_Write(LED_OFF);  
                                                                    break;}
                                                                    
                                            case STATUS_ON_BOTH: {  /* if we sample both signals turn on the LED */ 
                                                                    LED_Write(LED_ON);
                                                                    break;}
                                                                    
                                            case STATUS_ON_PHOTO:{  LED_Write(LED_OFF);
                                                                    break;}
                                            
                                            case STATUS_ON_TMP:  {  LED_Write(LED_OFF);
                                                                    break;}
                                                                    
                                            
                                            default :             break;
                                          }
                                        
                                        reset_flags();
                                        
                                        previous_status = status;  
                                        }
    

  
}
/* [] END OF FILE */
