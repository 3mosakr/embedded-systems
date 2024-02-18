/* 
 * File:   ecu_layer.c
 * Author: sakr3
 *
 * Created on January 1, 2024, 10:56 PM
 */

#include "ecu_layer_init.h"


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = LED_OFF};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = LED_OFF};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = LED_OFF};



void ecu_layer_intialize(){
    Std_ReturnType ret = E_NOT_OK;
    
    led_initialize(&led1);
    led_initialize(&led2);
    led_initialize(&led3);
}
