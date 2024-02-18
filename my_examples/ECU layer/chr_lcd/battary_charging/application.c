/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

uint8 customChar1[] = {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00};
uint8 customChar2[] = {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00};
uint8 customChar3[] = {0x0E, 0x0A, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00};
uint8 customChar4[] = {0x0E, 0x0A, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};
uint8 customChar5[] = {0x0E, 0x0A, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};
uint8 customChar6[] = {0x0E, 0x0A, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};
uint8 customChar7[] = {0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00};

uint8 battary[][8] = {
    {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x11, 0x1F, 0x00},
    {0x0E, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00},
    {0x0E, 0x0A, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x00},
    {0x0E, 0x0A, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00},
    {0x0E, 0x0A, 0x11, 0x1F, 0x1F, 0x1F, 0x1F, 0x00},
    {0x0E, 0x0A, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00},
    {0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}
};

void battary_charging (void){
    for (uint8 i = 0; i < 7; ++i) {
            lcd_8bit_send_custom_char(&lcd2, 1, 20, battary[i], 0);__delay_ms(200);
        }
}

Std_ReturnType ret = E_OK;

int main() {

    application_initialize();
        
    
//    ret = lcd_4bit_send_string_pos(&lcd1, 1, 1, "software");
//    ret = lcd_8bit_send_string_pos(&lcd2, 1, 1, "loading");
    
    
    
    while (1) {
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar1, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar2, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar3, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar4, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar5, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar6, 0);__delay_ms(200);
//        ret = lcd_8bit_send_custom_char(&lcd2, 1, 20, customChar7, 0);__delay_ms(200);
        battary_charging ();
        
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();

}