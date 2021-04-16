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

extern uint8_t flag;
extern uint16_t TMP_Array[SAMPLES];
extern uint16_t PHOTO_Array[SAMPLES];

CY_ISR(Custom_ISR_ADC)
{
    TIMER_ReadStatusRegister();
    if (flag != 5)
    {
        ADC_DelSig_AMux_Select(AMUX_PHOTO);
        PHOTO_Array[flag] = ADC_DelSig_Read16();
        if (PHOTO_Array[flag] < 0) PHOTO_Array[flag] =0;
        if (PHOTO_Array[flag] > 65535) PHOTO_Array[flag] =65535;
        PHOTO_Array[flag] = ADC_DelSig_CountsTo_mVolts(PHOTO_Array[flag]);
        
        ADC_DelSig_AMux_Select(AMUX_TMP);
        TMP_Array[flag] = ADC_DelSig_Read16();
        if (TMP_Array[flag] < 0) TMP_Array[flag] =0;
        if (TMP_Array[flag] > 65535) TMP_Array[flag] =65535;
        TMP_Array[flag] = ADC_DelSig_CountsTo_mVolts(TMP_Array[flag]);
        flag++;
    }
    
}
/* [] END OF FILE */
