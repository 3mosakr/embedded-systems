/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

uint16 adc_res_1=0;
uint16 adc_res_2=0;
uint16 adc_res_3=0;
uint16 adc_res_4=0;

adc_conf_t adc_1 = {
    .InterruptHandler = NULL,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERANCE_DISABLE
};

Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
    
    
    while (1) {
        ret = ADC_GetConversion_blocking(&adc_1, ADC_CHANNEL_AN0, &adc_res_1);
        ret = ADC_GetConversion_blocking(&adc_1, ADC_CHANNEL_AN1, &adc_res_2);
        ret = ADC_GetConversion_blocking(&adc_1, ADC_CHANNEL_AN2, &adc_res_3);
        ret = ADC_GetConversion_blocking(&adc_1, ADC_CHANNEL_AN3, &adc_res_4);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();
    
    ADC_Init(&adc_1);
}