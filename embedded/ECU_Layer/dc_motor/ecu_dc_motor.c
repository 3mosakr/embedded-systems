
#include "ecu_dc_motor.h"

/**
 * @brief Initialize the assigned pins to be output and turn the motor off or on
 * @param _dc_motor pointer to the motor module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType dc_motor_intialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == _dc_motor) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]));
        ret = gpio_pin_initialize(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]));
    }

    return ret;
}

/**
 * @brief Move the motor to the right direction
 * @param _dc_motor pointer to the motor module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == _dc_motor) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_LOW);
    }

    return ret;
}

/**
 * @brief Move the motor to the left direction
 * @param _dc_motor pointer to the motor module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == _dc_motor) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_HIGH);
    }

    return ret;
}

/**
 * @brief Stop the motor movement
 * @param _dc_motor pointer to the motor module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if (NULL == _dc_motor) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN1]), GPIO_LOGIC_LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[DC_MOTOR_PIN2]), GPIO_LOGIC_LOW);
    }

    return ret;
}
