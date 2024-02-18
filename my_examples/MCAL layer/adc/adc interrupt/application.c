/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

chr_lcd_4bit_t lcd1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOGIC_LOW,

    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOGIC_LOW,

    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOGIC_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOGIC_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOGIC_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOGIC_LOW
};

void lcd_init_message(const chr_lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    ret = lcd_4bit_send_string_pos(lcd, 1, 7, "ADC Test");
    __delay_ms(1500);
    ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);

    ret = lcd_4bit_send_string_pos(lcd, 1, 1, "Pot0: ");
    ret = lcd_4bit_send_string_pos(lcd, 2, 1, "Pot1: ");
    ret = lcd_4bit_send_string_pos(lcd, 3, 1, "Pot2: ");
    ret = lcd_4bit_send_string_pos(lcd, 4, 1, "Pot3: ");
}

/////////////////////////////////

uint16 adc_res_1, adc_res_2, adc_res_3, adc_res_4;
uint8 adc_res_1_txt[6], adc_res_2_txt[6], adc_res_3_txt[6], adc_res_4_txt[6];
uint8 ADC_Req;

void ADC_DefaultInterruptHandler(void);

adc_conf_t adc_1 = {
    .InterruptHandler = ADC_DefaultInterruptHandler,
    .acquisition_time = ADC_12_TAD,
    .adc_channel = ADC_CHANNEL_AN0,
    .conversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    .result_format = ADC_RESULT_RIGHT,
    .voltage_reference = ADC_VOLTAGE_REFERANCE_DISABLE
};



Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
    lcd_init_message(&lcd1);

    while (1) {
        if (0 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN0);
        } else if (1 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN1);
        } else if (2 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN2);
        } else if (3 == ADC_Req) {
            ret = ADC_StartConversion_Interrupt(&adc_1, ADC_CHANNEL_AN3);
        } else {
            /* NOTHING */
        }

        ret = convert_uint16_to_string(adc_res_1, adc_res_1_txt);
        ret = convert_uint16_to_string(adc_res_2, adc_res_2_txt);
        ret = convert_uint16_to_string(adc_res_3, adc_res_3_txt);
        ret = convert_uint16_to_string(adc_res_4, adc_res_4_txt);

        ret = lcd_4bit_send_string_pos(&lcd1, 1, 7, adc_res_1_txt);
        ret = lcd_4bit_send_string_pos(&lcd1, 2, 7, adc_res_2_txt);
        ret = lcd_4bit_send_string_pos(&lcd1, 3, 7, adc_res_3_txt);
        ret = lcd_4bit_send_string_pos(&lcd1, 4, 7, adc_res_4_txt);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

    ADC_Init(&adc_1);
    lcd_4bit_intialize(&lcd1);
}

/* ADC application ISR */
void ADC_DefaultInterruptHandler() {
    /* get the ADC conversion result */
    if (0 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &adc_res_1);
            ADC_Req = 1;
        } else if (1 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &adc_res_2);
            ADC_Req = 2;
        } else if (2 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &adc_res_3);
            ADC_Req = 3;
        } else if (3 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &adc_res_4);
            ADC_Req = 0;
        } else {
            /* NOTHING */
        }
    
}