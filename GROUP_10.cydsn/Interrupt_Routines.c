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
    if (flagPacketReady == 0)
    {
        
        ADC_DelSig_AMux_FastSelect(AMUX_PHOTO);
        //ADC_DelSig_StartConvert();
        /*PHOTO_Array[flag] = ADC_DelSig_Read32();
        if (PHOTO_Array[flag] < 0) PHOTO_Array[flag] =0;
        if (PHOTO_Array[flag] > 65535) PHOTO_Array[flag] =65535;
        PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(PHOTO_Array[flag]);
        */
        value_digit= ADC_DelSig_Read32();
        //ADC_DelSig_StopConvert();//binary value
        if(value_digit < 0) value_digit = 0;
        if(value_digit > 65535) value_digit = 35535 ;
        PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
        
        
        ADC_DelSig_AMux_FastSelect(AMUX_TMP);
        //ADC_DelSig_StartConvert();
        /*TMP_Array[flag] = ADC_DelSig_Read32();
        if (TMP_Array[flag] < 0) TMP_Array[flag] =0;
        if (TMP_Array[flag] > 65535) TMP_Array[flag] =65535;
        TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(TMP_Array[flag]);*/
        value_digit= ADC_DelSig_Read32();
        //ADC_DelSig_StopConvert();
        if(value_digit < 0) value_digit = 0;
        if(value_digit > 65535) value_digit = 35535 ;
        TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(value_digit);
        flag++;
    }
    
}
/* [] END OF FILE */
