/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"


segment_t seg1 = {
  .segment_pins[0].port = PORTC_INDEX,
  .segment_pins[0].pin = GPIO_PIN0,
  .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[0].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[1].port = PORTC_INDEX,
  .segment_pins[1].pin = GPIO_PIN1,
  .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[1].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[2].port = PORTC_INDEX,
  .segment_pins[2].pin = GPIO_PIN2,
  .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[2].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[3].port = PORTC_INDEX,
  .segment_pins[3].pin = GPIO_PIN3,
  .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[3].logic = GPIO_LOGIC_LOW,
  
  .segment_type = SEGMENT_COMMON_ANODE
};

pin_config_t seg1_enable = {
  .port = PORTD_INDEX,
  .pin = GPIO_PIN0,
  .direction = GPIO_DIRECTION_OUTPUT,
  .logic = GPIO_LOGIC_LOW
};

pin_config_t seg2_enable = {
  .port = PORTD_INDEX,
  .pin = GPIO_PIN1,
  .direction = GPIO_DIRECTION_OUTPUT,
  .logic = GPIO_LOGIC_LOW
};

Std_ReturnType ret = E_NOT_OK;

uint8 number = 0, counter = 0;

int main() {

    application_initialize();

    while (1) {
        for(counter = 0; counter < 50; ++counter){
            ret = seven_segment_write_number(&seg1, (uint8)(number/10));
            ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOGIC_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&seg1_enable, GPIO_LOGIC_LOW);

            ret = seven_segment_write_number(&seg1, (uint8)(number%10));
            ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOGIC_HIGH);
            __delay_ms(10);
            ret = gpio_pin_write_logic(&seg2_enable, GPIO_LOGIC_LOW);
        }
        number++;
        if(number == 99){
            number = 0;
        }
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {

    ret = seven_segment_initialize(&seg1);
    
    ret = gpio_pin_initialize(&seg1_enable);
    ret = gpio_pin_initialize(&seg2_enable);
    
}