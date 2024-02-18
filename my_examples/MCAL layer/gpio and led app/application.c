/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

/*
 gpio layer test
 
pin_config_t led_1 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOGIC_LOW
};
pin_config_t led_2 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOGIC_LOW
};
pin_config_t led_3 = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOGIC_LOW
};

pin_config_t btn_1 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_INPUT,
    .logic = GPIO_LOGIC_LOW
};

Std_ReturnType ret = E_NOT_OK; 

direction_t led_1_st;
logic_t pin_logic_st;
uint8 portc_logic_st;
*/

led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = LED_OFF};
led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = LED_OFF};
led_t led3 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN2, .led_status = LED_OFF};
led_t led4 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN3, .led_status = LED_OFF};


int main() {
    
    application_initialize ();
    
    while(1)
    {
        /* 
         * gpio layer test
        ret = gpio_port_toggle_logic(PORTC_INDEX);
        ret = gpio_port_read_logic(PORTC_INDEX, &portc_logic_st);
        __delay_ms(500);
        
        ret = gpio_pin_read_logic(&btn_1, &pin_logic_st);
        if (pin_logic_st == GPIO_LOGIC_HIGH){
            ret = gpio_pin_write_logic(&led_1, GPIO_LOGIC_HIGH);
        }else{
            ret = gpio_pin_write_logic(&led_1, GPIO_LOGIC_LOW);
        }
        ret = gpio_pin_toggle_logic(&led_2);
        ret = gpio_pin_toggle_logic(&led_3);
        __delay_ms(250);
         */
        
        /* 
        led_turn_on(&led1);
        led_turn_on(&led2);
        led_turn_on(&led3);
        led_turn_on(&led4);
        __delay_ms(250);
        led_turn_off(&led1);
        led_turn_off(&led2);
        led_turn_off(&led3);
        led_turn_off(&led4);
        __delay_ms(250);
        */
        led_turn_toggle(&led1);
        led_turn_toggle(&led2);
        led_turn_toggle(&led3);
        led_turn_toggle(&led4);
        __delay_ms(250);
    }
    return (EXIT_SUCCESS);
}


void application_initialize (void){
    /* 
     * gpio layer test
    ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
    ret = gpio_port_write_logic(PORTC_INDEX, 0x55);
    
    
    ret = gpio_pin_initialize(&led_1);
    ret = gpio_pin_get_direction_status(&led_1, &led_1_st);
    
    ret = gpio_pin_initialize(&led_2);
    
    ret = gpio_pin_initialize(&led_3);
    
//    ret = gpio_pin_initialize(NULL);
    
//    ret = gpio_pin_initialize(&btn_1);
    
    ret = gpio_port_direction_initialize(PORTD_INDEX, 0x55);
    
    */
    
    Std_ReturnType ret = E_NOT_OK;
    ret = led_initialize(&led1);
    ret = led_initialize(&led2);
    ret = led_initialize(&led3);
    ret = led_initialize(&led4);
    
    
}