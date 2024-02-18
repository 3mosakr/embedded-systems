/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

void welcome_message(const chr_lcd_4bit_t *lcd){
    lcd_4bit_send_string_pos(lcd, 1, 1, "welcome sir");
    __delay_ms(250);
    lcd_4bit_send_command(lcd, _LCD_CLEAR);
    __delay_ms(200);
    lcd_4bit_send_string_pos(lcd, 1, 1, "welcome sir");
    __delay_ms(250);
    lcd_4bit_send_command(lcd, _LCD_CLEAR);
    __delay_ms(200);
}

void loading_screen(const chr_lcd_8bit_t *lcd) {
    lcd_8bit_send_string_pos(lcd, 1, 1, "loading");
    for(uint8 i = 8; i < 15; ++i) {
        lcd_8bit_send_char_data_pos(lcd, 1, i, '.');
        __delay_ms(50);
    }
    lcd_8bit_send_string_pos(lcd, 1, 8, "       ");
    __delay_ms(50);
}

Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
        
    welcome_message(&lcd1);
//    ret = lcd_4bit_send_string_pos(&lcd1, 1, 1, "software");
//    ret = lcd_8bit_send_string_pos(&lcd2, 1, 1, "loading");
    

    while (1) {
        loading_screen(&lcd2);
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

}