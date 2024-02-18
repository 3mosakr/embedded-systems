/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

dc_motor_t motor1 = {
  .dc_motor_pin[0].port = PORTC_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN0,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
  
  .dc_motor_pin[1].port = PORTC_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN1,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS
};

dc_motor_t motor2 = {
  .dc_motor_pin[0].port = PORTC_INDEX,
  .dc_motor_pin[0].pin = GPIO_PIN2,
  .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[0].logic = DC_MOTOR_OFF_STATUS,
  
  .dc_motor_pin[1].port = PORTC_INDEX,
  .dc_motor_pin[1].pin = GPIO_PIN3,
  .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
  .dc_motor_pin[1].logic = DC_MOTOR_OFF_STATUS
};


Std_ReturnType ret = E_NOT_OK;

int main() {

    application_initialize();

    while (1) {
        ret = dc_motor_move_right(&motor1);
        ret = dc_motor_move_right(&motor2);
        __delay_ms(2000);
        ret = dc_motor_stop(&motor1);
        ret = dc_motor_stop(&motor2);
        __delay_ms(2000);
        ret = dc_motor_move_left(&motor1);
        ret = dc_motor_move_left(&motor2);
        __delay_ms(2000);
        ret = dc_motor_stop(&motor1);
        ret = dc_motor_stop(&motor2);
        __delay_ms(2000);
    }
    
    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    
    ret = dc_motor_intialize(&motor1);
    ret = dc_motor_intialize(&motor2);

}