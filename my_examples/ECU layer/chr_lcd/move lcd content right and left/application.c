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

    ret = lcd_8bit_send_string_pos(&lcd2, 1, 1, "software");

    while (1) {
        //        led_turn_on(&led1);
//        ret = lcd_4bit_send_string_pos(&lcd1, 1, 1, "Embedded-Dip");
        /*
         
        ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(100);
        ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_RIGHT);
        __delay_ms(100);
        ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(100);
        ret = lcd_4bit_send_command(&lcd1, _LCD_DISPLAY_SHIFT_LEFT);
        __delay_ms(100);
         */
        uint8 l_lcd_counter = 0;
        for (l_lcd_counter = 5; l_lcd_counter < 8; ++l_lcd_counter)
        {
            ret = lcd_4bit_send_string_pos(&lcd1, 1, l_lcd_counter, "Embedded-Dip");
            __delay_ms(150);
            ret = lcd_4bit_send_char_data_pos(&lcd1, 1, l_lcd_counter, ' ');
//            ret = lcd_4bit_send_string_pos(&lcd1, 1, l_lcd_counter, "            ");
        }
        ret = lcd_4bit_send_string_pos(&lcd1, 1, 5, "               ");
        
        for (; l_lcd_counter > 5; --l_lcd_counter)
        {
            ret = lcd_4bit_send_string_pos(&lcd1, 1, l_lcd_counter, "Embedded-Dip");
            __delay_ms(150);
            ret = lcd_4bit_send_char_data_pos(&lcd1, 1, l_lcd_counter+11, ' ');
//            ret = lcd_4bit_send_string_pos(&lcd1, 1, l_lcd_counter, "            ");
        }
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

}