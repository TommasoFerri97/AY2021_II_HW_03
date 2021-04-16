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

volatile uint8_t flagPacketReady = 0;
volatile uint8_t flag = 0;
//static char message[20] = {'\0'};
uint16_t TMP_Array[SAMPLES];
uint16_t PHOTO_Array[SAMPLES];
int i;
uint16_t sum_PHOTO,sum_TMP,mean_PHOTO,mean_TMP;
int main(void)
{
    TIMER_Start();
    ADC_DelSig_Start();
    UART_Start();
    isr_ADC_StartEx(Custom_ISR_ADC);
    ADC_DelSig_StartConvert();
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        if (flag == 5)
            {
                flagPacketReady = 1;
                for(i=0;i<5;i++)
                {
                    sum_PHOTO += PHOTO_Array[i];
                    sum_TMP += TMP_Array[i];
                }
                mean_PHOTO = sum_PHOTO/SAMPLES;
                mean_TMP = sum_TMP/SAMPLES;
                
                LED_Write(0);
                flag = 0;
                flagPacketReady = 0;
            }
            else
            {
                LED_Write(1);
                //UART_PutString("not working\r\n");
            }
       
    }
}
