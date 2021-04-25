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
0x03	TMP Bit 15-8	R
0x04	TMP Bit 07-0	R
0x05	PHOTO Bit 15-8	R
0x06	PHOTO Bit 07-0	R
*/

volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE] = {0};

uint16_t mean_PHOTO,mean_TMP;
uint16_t R_PHOTO;

int main(void)
{

    CyGlobalIntEnable; /* Enable global interrupts. */
  
    
    //ADC start
    ADC_DelSig_Start(); //NON METTO STARTCONVERT
    //timer init
    TIMER_Start();
    //isr start
    isr_ADC_StartEx(Custom_ISR_ADC);
    
    //I2C start
    EZI2C_Start ();
    //MUX_init
    AMux_1_Start();
    
    //initialize slavebuffer values
    
    SlaveBuffer[2] = WHO_AM_I;               // 0xBC
    
    //initialize flag
    reset_flags();
    status = 0;
    previous_status = 0;
    previous_N_samples = 0;
    period = SlaveBuffer[1]; //0
    previous_period = TIMER_ReadPeriod();   //39
    
    // Set up EZI2C buffer
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,SlaveBuffer);

    for(;;)
    
    {  
        
        if ( counter == N_samples){

                
                mean_PHOTO = ADC_DelSig_CountsTo_mVolts (sum_PHOTO/N_samples);
                mean_TMP = ADC_DelSig_CountsTo_mVolts (sum_TMP/N_samples);
            
                // byte SPLIT
                SlaveBuffer[3] = mean_TMP >>8;
                SlaveBuffer[4] = mean_TMP & 0xFF;
                SlaveBuffer[5] = mean_PHOTO >>8;    //HBYTES
                SlaveBuffer[6] = mean_PHOTO & 0xFF; //LBYTES
                
                reset_flags();
             
        }

        

    }
}
