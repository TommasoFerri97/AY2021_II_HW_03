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
#include "project.h"
#include "Interrupt_Routines.h"
#include "I2C_Interface.h"

/*STRUTTURA SLAVEBUFFER 
0x00	Control Reg 1	R/W
0x01	Control Reg 2	R/W
0x02	Who Am I	    R
0x03	PHOTO Bit 15-8	R
0x04	PHOTO Bit 07-0	R
0x05	TMP Bit 15-8	R
0x06	TMP Bit 07-0	R
*/

volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE] = {0};

int i;
int64 sum_PHOTO,sum_TMP; // 32? Bisogna controllare i casi limite con rischio overflow 
uint16_t mean_PHOTO,mean_TMP;

int main(void)
{

    CyGlobalIntEnable; /* Enable global interrupts. */
  
    //timer init
    TIMER_Start();
    //ADC start
    ADC_DelSig_Start();
    //isr start
    isr_ADC_StartEx(Custom_ISR_ADC);
    //I2C start
    EZI2C_Start ();
    //MUX_init
    AMux_1_Start();
    
    //initialize slavebuffer values
    
    SlaveBuffer[0] = _5_SAMPLES_OFF;        // 5 samples are averaged and device is stopped DA CAMBIARE CON CONTROL PANEL
    SlaveBuffer[1] = TIMER_ReadPeriod();     // Set period to 200 to get 4 ms
    SlaveBuffer[2] = WHO_AM_I;               // 0xBC
    
    //initialize flag
    flag = 0;
    counter = 0;
    status = (SlaveBuffer[0] & MASK);
    previous_status = status;

    // Set up EZI2C buffer
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,SlaveBuffer);

    for(;;)
    
    {  
        
        if (flag ==1 ){  
               
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
 
            
        if (counter == ITS_TIME_TO_SEND){
            
                mean_PHOTO = sum_PHOTO/SAMPLES; 
                mean_TMP = sum_TMP/SAMPLES;
                
                // byte SPLIT
                SlaveBuffer[3] = mean_PHOTO >>8;    //HBYTES
                SlaveBuffer[4] = mean_PHOTO & 0xFF; //LBYTES
                SlaveBuffer[5] = mean_TMP >>8;
                SlaveBuffer[6] = mean_TMP & 0xFF;
                
                flag=0;
                counter=0;
                sum_PHOTO = 0;
                sum_TMP = 0;
        }
        
   
        

    }
}
