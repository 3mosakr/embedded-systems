/* 
 * File:   ecu_seven_seg.c
 * Author: sakr3
 *
 * Created on December 20, 2023, 4:10 PM
 */

#include "ecu_seven_seg.h"

/**
 * @brief make the needed GPIO and segment initialization
 * @param seg pointer to the segment module configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType seven_segment_initialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if (NULL == seg) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(seg->segment_pins[SEGMENT_PIN3]));
    }

    return ret;
}

/**
 * @brief write number to the seven segment throw decoder 0 ~ 9
 * @param seg pointer to the segment module configurations
 * @param number the number which will write in seven segment
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number){
    Std_ReturnType ret = E_OK;
    if ((NULL == seg) || ((number < 0)&&(number > 9))) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN0]), READ_BIT(number, 0));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN1]), READ_BIT(number, 1));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN2]), READ_BIT(number, 2));
        ret = gpio_pin_write_logic(&(seg->segment_pins[SEGMENT_PIN3]), READ_BIT(number, 3));
    }

    return ret;
}

