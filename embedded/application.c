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

dc_motor_t motor1 = {
  .dc_motor_pin[0].port = PORTD_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN0,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
  
  .dc_motor_pin[1].port = PORTD_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN1,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS
};

dc_motor_t motor2 = {
  .dc_motor_pin[0].port = PORTD_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN2,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
  
  .dc_motor_pin[1].port = PORTD_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN3,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS
};

void lcd_init_message(const chr_lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    ret = lcd_4bit_send_string_pos(lcd, 1, 2, "ADC, LCD, LM35 Test");
    __delay_ms(500);

    ret = lcd_4bit_send_string_pos(lcd, 2, 1, "Temp1: ");
    ret = lcd_4bit_send_string_pos(lcd, 3, 1, "Temp2: ");
}

/////////////////////////////////

uint16 LM35_res_1, LM35_res_2, LM35_res_1_Celsius_mv, LM35_res_2_Celsius_mv;
uint8 LM35_res_1_txt[6], LM35_res_2_txt[6];
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
        }  else {
            /* NOTHING */
        }
        
        LM35_res_1_Celsius_mv = LM35_res_1 * 4.8875f;
        LM35_res_1_Celsius_mv /= 10;
        
        LM35_res_2_Celsius_mv = LM35_res_2 * 4.8875f;
        LM35_res_2_Celsius_mv /= 10;
        
        if(LM35_res_1_Celsius_mv > 20){
            dc_motor_move_right(&motor1);
        }else {
            dc_motor_stop(&motor1);
        }
        
        if(LM35_res_2_Celsius_mv > 25){
            dc_motor_move_right(&motor2);
        }else {
            dc_motor_stop(&motor2);
        }
        
        ret = convert_uint16_to_string(LM35_res_1_Celsius_mv, LM35_res_1_txt);
        ret = convert_uint16_to_string(LM35_res_2_Celsius_mv, LM35_res_2_txt);

        ret = lcd_4bit_send_string_pos(&lcd1, 2, 8, LM35_res_1_txt);
        ret = lcd_4bit_send_string_pos(&lcd1, 3, 8, LM35_res_2_txt);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

    ADC_Init(&adc_1);
    lcd_4bit_intialize(&lcd1);
    dc_motor_intialize(&motor1);
    dc_motor_intialize(&motor2);
}

/* ADC application ISR */
void ADC_DefaultInterruptHandler() {
    /* get the ADC conversion result */
    if (0 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &LM35_res_1);
            ADC_Req = 1;
        } else if (1 == ADC_Req) {
            ADC_GetConversionResult(&adc_1, &LM35_res_2);
            ADC_Req = 0;
        } else {
            /* NOTHING */
        }
    
}