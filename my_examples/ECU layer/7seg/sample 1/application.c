/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"

// uint8 seg_common_anode_values[10] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90};

Std_ReturnType ret = E_NOT_OK;
// uint8 ones = 0, tens = 0;
uint8 num = 0, num_bcd = 0;

int main() {

    application_initialize();
    
    while (1) {
        num_bcd = (((uint8) num % 10) | (((uint8) num / 10) << 4));
        ret = gpio_port_write_logic(PORTC_INDEX, num_bcd);
        if(num == 99){
            num = 0;
        }
        else{}
        num++;
        __delay_ms(150);
        
        
        /*
        for(tens = 0; tens < 10; tens++){
            ret = gpio_port_write_logic(PORTD_INDEX, seg_common_anode_values[tens]);
            for(ones = 0; ones < 10; ones++){
                ret = gpio_port_write_logic(PORTC_INDEX, seg_common_anode_values[ones]);
                __delay_ms(100);
            }
        }
         */
    }   
    
    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    
    ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
//    ret = gpio_port_direction_initialize(PORTD_INDEX, 0x80);
    
    ret = gpio_port_write_logic(PORTC_INDEX, 0);
//    ret = gpio_port_write_logic(PORTD_INDEX, 0x00);
    
}