/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

/*
 * button 


led_t led1 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN0, .led_status = GPIO_LOGIC_LOW};
//led_t led2 = {.port_name = PORTC_INDEX, .pin = GPIO_PIN1, .led_status = GPIO_LOGIC_LOW};

button_t btn_high = {
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOGIC_LOW,
    .button_connection = BUTTON_ACTIVE_HIGH,
    .button_state = BUTTON_RELEASED
};

void program1(void) {
    led_turn_on(&led1);
    __delay_ms(200);
    led_turn_off(&led1);
    __delay_ms(200);
}

void program2(void) {
    for (uint8 i = 0; i < 2; ++i) {
        led_turn_on(&led1);
        __delay_ms(200);
        led_turn_off(&led1);
        __delay_ms(200);
    }
}

void program3(void) {
    for (uint8 i = 0; i < 3; ++i) {
        led_turn_on(&led1);
        __delay_ms(200);
        led_turn_off(&led1);
        __delay_ms(200);
    }
}

Std_ReturnType ret = E_NOT_OK;
button_state_t btn_high_status = BUTTON_RELEASED;
button_state_t btn_high_valid_status = BUTTON_RELEASED;

uint16 btn_high_valid = 0;
uint8 program_selected = 0;
*/

relay_t relay1 = {
  .relay_port = PORTC_INDEX,
  .relay_pin = GPIO_PIN0,
  .relay_status = RELAY_OFF_STATUS
};

relay_t relay2 = {
  .relay_port = PORTC_INDEX,
  .relay_pin = GPIO_PIN1,
  .relay_status = RELAY_OFF_STATUS
};

Std_ReturnType ret = E_NOT_OK;

int main() {


    application_initialize();

    while (1) {
/* 
 *  * button 
        ret = button_read_state(&btn_high, &btn_high_status);

        if (BUTTON_PRESSED == btn_high_status) {
            btn_high_valid++;
            if (btn_high_valid > 200) {
                btn_high_valid_status = BUTTON_PRESSED;
            }
        } else {
            btn_high_valid = 0;
            btn_high_valid_status = BUTTON_RELEASED;
        }

        if (btn_high_valid_status == BUTTON_PRESSED) {
            program_selected++;

            switch (program_selected) {
                case 1: program1();
                    break;
                case 2: program2();
                    break;
                case 3: program3();
                    break;
                default: program_selected = 0;
                    break;
            }
        }
*/
        
        ret = relay_turn_on(&relay1);
        ret = relay_turn_off(&relay2);
        __delay_ms(3000);
        ret = relay_turn_off(&relay1);
        ret = relay_turn_on(&relay2);
        __delay_ms(3000);
    }
    return (EXIT_SUCCESS);
}

void application_initialize(void) {

    /*
     *  * button 
    ret = button_initialize(&btn_high);
    ret = led_initialize(&led1);
    */
   ret = relay_initialize(&relay1);
   ret = relay_initialize(&relay2);

}