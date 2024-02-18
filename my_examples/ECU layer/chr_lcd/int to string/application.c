/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"



Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
        
    
//    ret = lcd_4bit_send_string_pos(&lcd1, 1, 1, "software");
//    ret = lcd_8bit_send_string_pos(&lcd2, 1, 1, "loading");
    
    uint8 l_counter = 0;
    uint8 l_counter_str[4];
    ret = lcd_8bit_send_string(&lcd2, "counter: ");
    
    while (1) {
        convert_uint8_to_string(l_counter, l_counter_str);
        ret = lcd_8bit_send_string_pos(&lcd2, 1, 10, l_counter_str);
        if (255 == l_counter){
            ret = lcd_8bit_send_string_pos(&lcd2, 1, 10, "   ");
        }
        l_counter++;
        __delay_ms(10);
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

}