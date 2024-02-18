/* 
 * File:   ecu_layer.c
 * Author: sakr3
 *
 * Created on January 1, 2024, 10:56 PM
 */

#include "ecu_layer_init.h"


//led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = LED_OFF};

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

chr_lcd_8bit_t lcd2 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN6,
  .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic = GPIO_LOGIC_LOW,
  
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN7,
  .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic = GPIO_LOGIC_LOW,
  
  .lcd_data[0].port = PORTD_INDEX,
  .lcd_data[0].pin = GPIO_PIN0,
  .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic = GPIO_LOGIC_LOW,
  .lcd_data[1].port = PORTD_INDEX,
  .lcd_data[1].pin = GPIO_PIN1,
  .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic = GPIO_LOGIC_LOW,
  .lcd_data[2].port = PORTD_INDEX,
  .lcd_data[2].pin = GPIO_PIN2,
  .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic = GPIO_LOGIC_LOW,
  .lcd_data[3].port = PORTD_INDEX,
  .lcd_data[3].pin = GPIO_PIN3,
  .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic = GPIO_LOGIC_LOW,
  .lcd_data[4].port = PORTD_INDEX,
  .lcd_data[4].pin = GPIO_PIN4,
  .lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[4].logic = GPIO_LOGIC_LOW,
  .lcd_data[5].port = PORTD_INDEX,
  .lcd_data[5].pin = GPIO_PIN5,
  .lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[5].logic = GPIO_LOGIC_LOW,
  .lcd_data[6].port = PORTD_INDEX,
  .lcd_data[6].pin = GPIO_PIN6,
  .lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[6].logic = GPIO_LOGIC_LOW,
  .lcd_data[7].port = PORTD_INDEX,
  .lcd_data[7].pin = GPIO_PIN7,
  .lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
  .lcd_data[7].logic = GPIO_LOGIC_LOW
};

void ecu_layer_intialize(){
    Std_ReturnType ret = E_NOT_OK;
    
    ret = lcd_4bit_intialize(&lcd1);
    ret = lcd_8bit_intialize(&lcd2);
//    led_initialize(&led1);
}
