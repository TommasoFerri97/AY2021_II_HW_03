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
    TIMER_ReadStatusRegister();  //per ora usiamo solo counter come variabile non più flag. Può tornare utile se riduciamo i 4ms
    
    
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
    
    


void EZI2C_ISR_ExitCallback(void)
{   //Everytime we get a new command from bridge control panel, we check if the values are ok
 
    status = (SlaveBuffer[0] & MASK);
    
    if (status != previous_status)  {
        
                                      //SlaveBuffer[0] = SAMPLES<<2 | status;      //mantengo lo status scelto, fisso 5 samples sempre
                                      previous_status = status;  
                                      
                                      switch(status) {

                                      case STATUS_OFF:     {turn_off();          //if status bits are 00, we turn-off the system (LED, ADC, reset flag)
                                                            break;}
                                                            

                                      case STATUS_ON_BOTH: {turn_on ();
                                                            LED_Write(LED_ON);
                                                            break;}
                                                            
                                      case STATUS_ON_PHOTO:{turn_on ();
                                                            LED_Write(LED_OFF);
                                                            break;}
                                    
                                      case STATUS_ON_TMP:  {turn_on ();
                                                            LED_Write(LED_OFF);
                                                            break;}
                                                            
                                    
                                      default :             break;
                                      }
                                    }
    if (SlaveBuffer[1] != DEFAULT_PERIOD) SlaveBuffer[1] = DEFAULT_PERIOD;
    if (SlaveBuffer[2] != WHO_AM_I)       SlaveBuffer[2] = WHO_AM_I;
  
}
/* [] END OF FILE */
