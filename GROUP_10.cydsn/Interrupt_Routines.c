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

static int32 value_digit;
//static char message[20] = {'\0'};

CY_ISR(Custom_ISR_ADC)
{
    TIMER_ReadStatusRegister();

    if (status != STATUS_OFF) counter++; //Conto solo se non sono spento(serve se l'isr la lasciamo sempre attiva) il counter ora è a 2ms

    
    if (flag != PACKET_READY){          
        switch (status){
        
        
        case STATUS_ON_PHOTO: 
                                {PHOTO_Array[flag] = sample(AMUX_PHOTO);
                                //PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit); //taglia i 2 byte di troppo?
                                flag++;
                                break;}
                                
                                
        case STATUS_ON_TMP:     
                                {TMP_Array[flag]  = sample(AMUX_TMP);
                                //TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                flag++;
                                break;}
                                
        case STATUS_ON_BOTH:
                                {value_digit  = sample(AMUX_PHOTO);
                                PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);

                                value_digit  = sample(AMUX_TMP);
                                TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                flag++;
                                break;}
        default : break;
        }
        
 
    }
    
}

void EZI2C_ISR_ExitCallback(void)
{   //Everytime we get a new command from bridge control panel, we check if the values are ok
 
    status = (SlaveBuffer[0] & 0b00000011);                       //consider only the first 2 b
    
    if (SlaveBuffer[0]>>2 != SAMPLES ) {                                       
                                        SlaveBuffer[0] = SAMPLES<<2 | status; //mantengo lo status scelto, fisso 5 samples sempre
                                        }                                     //TUTTO FUNZIONA SIA CON 0x17 che 0x03 (esempio BOTH)
    if (SlaveBuffer[1] != DEFAULT_PERIOD) SlaveBuffer[1] = DEFAULT_PERIOD;
    if (SlaveBuffer[2] != WHO_AM_I)       SlaveBuffer[2] = WHO_AM_I;
    
    
    switch(status) {
        
    case STATUS_OFF:     {turn_off();            //if status bits are 00, we turn-off the system (LED, ADC, reset flag)
                         break;}
    
    case STATUS_ON_BOTH: {turn_on ();
                         LED_Write(LED_ON);
                         break;}
    
    default :            {turn_on();
                         LED_Write(LED_OFF);
                         break;}
     
    }

    
}
/* [] END OF FILE */
