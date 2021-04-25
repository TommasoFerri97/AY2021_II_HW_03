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
#include "cyapicallbacks.h"


CY_ISR(Custom_ISR_ADC)
{
    TIMER_ReadStatusRegister(); 
    
    if (status != STATUS_OFF && counter < N_samples){
    
        counter++;
        
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
    


void EZI2C_ISR_ExitCallback(void)
{   //Everytime we get a new command from bridge control panel
    
    //read the status
    status = (SlaveBuffer[0] & MASK);
    //read the Number of samples
    N_samples = (SlaveBuffer[0] >> 2);
    //read the period of the isr
    period = SlaveBuffer[1];
    
 
    
    //if the period has been changed, update it    
    //NOTE that the clock is 2kHz, therefore we need to multiply by 2 the value written by the user
    
    if ( period != previous_period )    {
                                        TIMER_WritePeriod((period*ms_to_count)-1);// setto il periodo nuovo (scelto dall'utente, o imposto se valori incompatibili)
                                        
                                        previous_period = period;
                                        }
    
   
    
    //if the status has been changed, update it   
    if ( status != previous_status )    {
                                        previous_status = status;  
                                      
                                        switch(status) {

                                        case STATUS_OFF:     {  
                                                                reset_flags();
                                                                LED_Write(LED_OFF);  
                                                                break;}
                                                                

                                        case STATUS_ON_BOTH: {   
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
