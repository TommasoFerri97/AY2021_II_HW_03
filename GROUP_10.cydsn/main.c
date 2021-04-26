/* ========================================
 * 
 * Group 10
 *  
 * File Name: main.c
 * 
 * PSoC Creator  4.4
 *
 * Description:
 * It contains the code to initialize peripherals, to compute the average and write into the slavebuffer registers
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

#include "project.h"
#include "Interrupt_Routines.h"
#include "I2C_Interface.h"

/* 
 * ========================================
 *
 * variables definitions and initialization;
 *
 * ========================================
*/ 

volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE];

/* 
   SLAVEBUFFER STRUCURE
0x00	Control Reg 1	R/W
0x01	Control Reg 2	R/W
0x02	Who Am I	    R
0x03	TMP Bit 15-8	R
0x04	TMP Bit 07-0	R
0x05	PHOTO Bit 15-8	R
0x06	PHOTO Bit 07-0	R
*/

uint16_t mean_PHOTO,mean_TMP;

/* 
 * ========================================
 *
 * main code definition;
 *
 * ========================================
*/ 

int main(void)
{

    /* ADC start */
    
    ADC_DelSig_Start(); 
    
    /* TIMER start */
    
    TIMER_Start();
    
    /* ISR start */
    
    isr_ADC_StartEx(Custom_ISR_ADC);
    
    /* I2C start */
    
    EZI2C_Start ();
    
    /* MUX_init */
    
    AMux_1_Start();
    
    /* initialize SlaveBuffer registers */
    
    SlaveBuffer[0] &= MASK_RESERVED;  /* initialize the buffer to 0, don't change the Reserved bits*/ 
    SlaveBuffer[1] |= 0x00;
    SlaveBuffer[2] |= WHO_AM_I;        /* 0xBC */
    SlaveBuffer[3] |= 0x00;
    SlaveBuffer[4] |= 0x00;
    SlaveBuffer[5] |= 0x00;
    SlaveBuffer[6] |= 0x00;
    
    /* initialize flag */ 
    
    reset_flags();
    status = 0;
    previous_status = 0;
    period = SlaveBuffer[1]; 
    previous_period = period ;   
     
    /* Set up EZI2C Read only data bytes  */
    
    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,SlaveBuffer);
    
    /* Enable global interrupts. */
    
    CyGlobalIntEnable; 
    
    for(;;)
    
    {  
        
        if ( counter == N_samples){

                /* convert to mV the average of aquired data */
            
                mean_PHOTO = ADC_DelSig_CountsTo_mVolts (sum_PHOTO/N_samples);
                mean_TMP = ADC_DelSig_CountsTo_mVolts (sum_TMP/N_samples);
            
                /* byte SPLIT */
                
                /* HBYTES */
                
                SlaveBuffer[3] = mean_TMP >>8;
                SlaveBuffer[5] = mean_PHOTO >>8;
                
                /* LBYTES */ 
                
                SlaveBuffer[4] = mean_TMP & 0xFF;
                SlaveBuffer[6] = mean_PHOTO & 0xFF;    
                
                /* reset flags to start a new cycle */
                
                reset_flags();
             
        }

        

    }
}
