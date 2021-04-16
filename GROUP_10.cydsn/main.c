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



uint8_t SlaveBuffer[SLAVE_BUFFER_SIZE] = {0};

volatile uint8_t flagPacketReady = 0;
volatile uint8_t flag = 0;
//static char message[20] = {'\0'};
uint16_t TMP_Array[SAMPLES];
uint16_t PHOTO_Array[SAMPLES];
int i;
uint16_t sum_PHOTO,sum_TMP,mean_PHOTO,mean_TMP;

int main(void)
{

    CyGlobalIntEnable; /* Enable global interrupts. */

    //timer init
    TIMER_Start();
    //ADC init
    ADC_DelSig_Start();
    //Uart init for debug 
    UART_Start();
    //ISR start with external custom function
    isr_ADC_StartEx(Custom_ISR_ADC);
    
    //initialize slavebuffer values
    SlaveBuffer[0] = _5_SAMPLES_OFF;         // 5 samples are averaged and device is stopped DA CAMBIARE CON CONTROL PANEL
    SlaveBuffer[1] = TIMER_ReadPeriod();     // Set period to 200 to get 4 ms
    SlaveBuffer[2] = WHO_AM_I;               // 0xBC

    
    //start conversion
    ADC_DelSig_StartConvert();
    
    for(;;)
    {
        if (flagPacketReady == 1)
            {
                for(i=0;i<SAMPLES;i++)
                {
                    sum_PHOTO += PHOTO_Array[i];
                    sum_TMP += TMP_Array[i];
                }
                mean_PHOTO = sum_PHOTO/SAMPLES;
                mean_TMP = sum_TMP/SAMPLES;
                
                
                flag = 0;
                flagPacketReady = 0;
            }
            else
            {
                
                //UART_PutString("not working\r\n");
            }
       
    }
}
