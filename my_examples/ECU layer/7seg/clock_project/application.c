/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"


Std_ReturnType ret = E_NOT_OK;

uint8 second = 50, minutes = 59, hours = 23;

uint8 counter = 0;

int main() {

    application_initialize();

    while (1) {
        for (counter = 0; counter < 50; counter++) {
            ret = gpio_port_write_logic(PORTD_INDEX, 0x1F);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (second % 10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x2F);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (second / 10)));
            __delay_us(3333);

            ret = gpio_port_write_logic(PORTD_INDEX, 0x37);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (minutes % 10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x3B);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (minutes / 10)));
            __delay_us(3333);

            ret = gpio_port_write_logic(PORTD_INDEX, 0x3D);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (hours % 10)));
            __delay_us(3333);
            ret = gpio_port_write_logic(PORTD_INDEX, 0x3E);
            ret = gpio_port_write_logic(PORTC_INDEX, ((uint8) (hours / 10)));
            __delay_us(3333);
        }

        second++;

        if (60 == second) {
            second = 0;
            minutes++;
        }
        if (60 == minutes) {
            minutes = 0;
            hours++;
        }
        if (24 == hours) {
            hours = 0;
        }
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {

    ret = gpio_port_direction_initialize(PORTC_INDEX, 0xF0);
    ret = gpio_port_direction_initialize(PORTD_INDEX, 0xC0);

    ret = gpio_port_write_logic(PORTC_INDEX, 0);
}