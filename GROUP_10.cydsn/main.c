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



volatile uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE] = {0};

/*STRUTTURA SLAVEBUFFER 
0x00	Control Reg 1	R/W
0x01	Control Reg 2	R/W
0x02	Who Am I	    R
0x03	PHOTO Bit 15-8	R
0x04	PHOTO Bit 07-0	R
0x05	TMP Bit 15-8	R
0x06	TMP Bit 07-0	R
*/


//static char message[20] = {'\0'};
//static uint16_t out_PHOTO,out_TMP;

int i;
uint16_t sum_PHOTO,sum_TMP,mean_PHOTO,mean_TMP;

int main(void)
{

    CyGlobalIntEnable; /* Enable global interrupts. */

    //timer init
    TIMER_Start();
    //ADC init
    ADC_DelSig_Start();
    
    //Uart init for debug??? 
    //UART_Start();
    
    //isr start
    isr_ADC_StartEx(Custom_ISR_ADC);

    //I2C init
    EZI2C_Start ();
    
    //initialize slavebuffer values
    SlaveBuffer[0] = _5_SAMPLES_OFF;         // 5 samples are averaged and device is stopped DA CAMBIARE CON CONTROL PANEL
    SlaveBuffer[1] = TIMER_ReadPeriod();     // Set period to 100 to get 2 ms
    SlaveBuffer[2] = WHO_AM_I;               // 0xBC
    
    //initialize flag
    flag = 0;
    counter = 0;
    status = 0x00;
    
    //start conversion
    ADC_DelSig_StartConvert();
    
    
    // Set up EZI2C buffer

    EZI2C_SetBuffer1(SLAVE_BUFFER_SIZE, BUFFER_RW_AREA_SIZE ,SlaveBuffer);
    
    for(;;)
    {     
        
        if (flag == PACKET_READY )
            {
                for(i=0;i<SAMPLES;i++)
                {
                    sum_PHOTO += PHOTO_Array[i];
                    sum_TMP += TMP_Array[i];
                }
                mean_PHOTO = sum_PHOTO/SAMPLES;
                mean_TMP = sum_TMP/SAMPLES;
                // byte SPLIT
                SlaveBuffer[3] = mean_PHOTO >>8;    //HBYTES
                SlaveBuffer[4] = mean_PHOTO & 0xFF; //LBYTES
                SlaveBuffer[5] = mean_TMP >>8;
                SlaveBuffer[6] = mean_TMP & 0xFF;
                //out_PHOTO = ((int16_t)((SlaveBuffer[4] | (SlaveBuffer[3] << 8))) >> 6) & 0xFFFF;
                //out_TMP = ((int16_t)((SlaveBuffer[6] | (SlaveBuffer[5] << 8))) >> 6) & 0xFFFF;
            }
        
        if (flag == PACKET_READY && counter == ITS_TIME_TO_SEND){
            //every 20 ms
            //reset flags
            counter = 0;
            flag = 0;
  
            }
    }
}
