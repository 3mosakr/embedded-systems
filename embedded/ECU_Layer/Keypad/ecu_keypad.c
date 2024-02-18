/* 
 * File:   ecu_keypad.c
 * Author: sakr3
 *
 * Created on December 23, 2023, 11:26 AM
 */

#include "ecu_keypad.h"

static const uint8 btn_value[ECU_KEYPAD_ROWS][ECU_KEYPAD_columns] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'},
                                                                    };

/**
 * @brief initialize the keypad assigned pins
 * @param _keypad_obj pointer to the keypad configuration
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj) {
    Std_ReturnType ret = E_OK;
    if (NULL == _keypad_obj) {
        ret = E_NOT_OK;
    } else {
        uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
        
        for (rows_counter = ZERO_INIT; rows_counter < ECU_KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_initialize(&(_keypad_obj->keypad_row_pins[rows_counter]));
        }
        
        for (columns_counter = ZERO_INIT; columns_counter < ECU_KEYPAD_columns; columns_counter++){
            ret = gpio_pin_direction_initialize(&(_keypad_obj->keypad_columns_pin[columns_counter]));
        }
    }

    return ret;
}

/**
 * @brief get the value of the button pressed by the user and performing the scanning algorithm
 * @param _keypad_obj pointer to the keypad configuration
 * @param value value of the button pressed by the user
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value) {
    Std_ReturnType ret = E_OK;
    if ((NULL == _keypad_obj) || (NULL == value)) {
        ret = E_NOT_OK;
    } else {
        uint8 l_rows_counter = ZERO_INIT, l_columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
        uint8 column_logic = GPIO_LOGIC_LOW;
        
        // active the rows pins and scan the columns pins 
        for (l_rows_counter = ZERO_INIT; l_rows_counter < ECU_KEYPAD_ROWS; l_rows_counter++){
            // turn off all rows pins at first
            for (l_counter = ZERO_INIT; l_counter < ECU_KEYPAD_ROWS; l_counter++){
                ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_counter]), GPIO_LOGIC_LOW);
            }
            // active the row pin
            ret = gpio_pin_write_logic(&(_keypad_obj->keypad_row_pins[l_rows_counter]), GPIO_LOGIC_HIGH);
            // scan the columns pins 
            for (l_columns_counter = ZERO_INIT; l_columns_counter < ECU_KEYPAD_columns; l_columns_counter++){
                ret = gpio_pin_read_logic(&(_keypad_obj->keypad_columns_pin[l_columns_counter]), &column_logic);
                
                if (GPIO_LOGIC_HIGH == column_logic){
                    *value = btn_value[l_rows_counter][l_columns_counter];
                }
            }
        }
    }

    return ret;
}
