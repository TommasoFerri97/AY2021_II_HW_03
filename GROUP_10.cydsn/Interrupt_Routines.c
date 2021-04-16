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


extern uint16_t TMP_Array[SAMPLES];
extern uint16_t PHOTO_Array[SAMPLES];
int32 value_digit;


CY_ISR(Custom_ISR_ADC)
{
    TIMER_ReadStatusRegister();
    if (flagPacketReady == 0) // Serve per evitare di campionare mentre stiamo inviando? 
    {
        switch (SlaveBuffer[0]){
            
        case _5_SAMPLES_ON_LDR: LED_Write(0);
                                ADC_DelSig_AMux_FastSelect(AMUX_PHOTO); // usiamo il fast?
                                //ADC_DelSig_StartConvert();
                                value_digit= ADC_DelSig_Read32();
                                //ADC_DelSig_StopConvert();
                                if(value_digit < 0) value_digit = 0;
                                if(value_digit > 65535) value_digit = 35535 ;
                                PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                flag++;
                                break;
                                
        case _5_SAMPLES_ON_TMP: LED_Write(0);
                                ADC_DelSig_AMux_FastSelect(AMUX_TMP);
                                //ADC_DelSig_StartConvert();
                                value_digit= ADC_DelSig_Read32();
                                //ADC_DelSig_StopConvert();
                                if(value_digit < 0) value_digit = 0;
                                if(value_digit > 65535) value_digit = 35535 ;
                                PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                flag++;
                                break;
                                
        case _5_SAMPLES_ON_BOTH:
                                LED_Write(1);
                                ADC_DelSig_AMux_FastSelect(AMUX_PHOTO);
                                //ADC_DelSig_StartConvert();
                                value_digit= ADC_DelSig_Read32();
                                //ADC_DelSig_StopConvert();
                                if(value_digit < 0) value_digit = 0;
                                if(value_digit > 65535) value_digit = 35535 ;
                                PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                
                                
                                ADC_DelSig_AMux_FastSelect(AMUX_TMP);
                                //ADC_DelSig_StartConvert();
                                value_digit= ADC_DelSig_Read32();
                                //ADC_DelSig_StopConvert();
                                if(value_digit < 0) value_digit = 0;
                                if(value_digit > 65535) value_digit = 35535 ;
                                TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
                                flag++;
                                break;
        default : break;
        
        }
        
        if (flag ==5) flagPacketReady = 1; //ridondante: la doppia flag è utile solo se usiamo periodo < 4ms (da decidere, magari è meglio perchè così siamo un po' tirati)
        
        /*
        ADC_DelSig_AMux_FastSelect(AMUX_PHOTO);
        //ADC_DelSig_StartConvert();
        value_digit= ADC_DelSig_Read32();
        //ADC_DelSig_StopConvert();
        if(value_digit < 0) value_digit = 0;
        if(value_digit > 65535) value_digit = 35535 ;
        PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
        
        
        ADC_DelSig_AMux_FastSelect(AMUX_TMP);
        //ADC_DelSig_StartConvert();
        value_digit= ADC_DelSig_Read32();
        //ADC_DelSig_StopConvert();
        if(value_digit < 0) value_digit = 0;
        if(value_digit > 65535) value_digit = 35535 ;
        TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
        flag++;*/
    }
    
}
/* [] END OF FILE */
