/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"


keypad_t keypad1 = {
    .keypad_row_pins[0].port = PORTC_INDEX,
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[0].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[1].port = PORTC_INDEX,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[1].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[2].port = PORTC_INDEX,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[2].logic = GPIO_LOGIC_LOW,
    .keypad_row_pins[3].port = PORTC_INDEX,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_row_pins[3].logic = GPIO_LOGIC_LOW,
    .keypad_columns_pin[0].port = PORTC_INDEX,
    .keypad_columns_pin[0].pin = GPIO_PIN4,
    .keypad_columns_pin[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[0].logic = GPIO_LOGIC_LOW,
    .keypad_columns_pin[1].port = PORTC_INDEX,
    .keypad_columns_pin[1].pin = GPIO_PIN5,
    .keypad_columns_pin[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[1].logic = GPIO_LOGIC_LOW,
    .keypad_columns_pin[2].port = PORTC_INDEX,
    .keypad_columns_pin[2].pin = GPIO_PIN6,
    .keypad_columns_pin[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[2].logic = GPIO_LOGIC_LOW,
    .keypad_columns_pin[3].port = PORTC_INDEX,
    .keypad_columns_pin[3].pin = GPIO_PIN7,
    .keypad_columns_pin[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pin[3].logic = GPIO_LOGIC_LOW
};

segment_t seg1 = {
  .segment_pins[0].port = PORTA_INDEX,
  .segment_pins[0].pin = GPIO_PIN0,
  .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[0].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[1].port = PORTA_INDEX,
  .segment_pins[1].pin = GPIO_PIN1,
  .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[1].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[2].port = PORTA_INDEX,
  .segment_pins[2].pin = GPIO_PIN2,
  .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[2].logic = GPIO_LOGIC_LOW,
  
  .segment_pins[3].port = PORTA_INDEX,
  .segment_pins[3].pin = GPIO_PIN3,
  .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
  .segment_pins[3].logic = GPIO_LOGIC_LOW,
  
  .segment_type = SEGMENT_COMMON_ANODE
};

uint8 keypad_value = ZERO_INIT;

Std_ReturnType ret = E_OK;

int main() {

    application_initialize();

    while (1) {
        ret = keypad_get_value(&keypad1, &keypad_value);
        /* convert char to integer */
        
        ret = seven_segment_write_number(&seg1, (uint8)keypad_value);
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {

    ret = keypad_initialize(&keypad1);
    ret = seven_segment_initialize(&seg1);
    
}