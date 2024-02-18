/* 
 * File:   application.c
 * Author: sakr3
 *
 * Created on November 4, 2023, 11:49 AM
 */

#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"

volatile uint8 program_select = ZERO_INIT;

void int0_app_isr(void){
    program_select++;
    if(3 == program_select){
        program_select = 0;
    }
    else{}
    Data_EEPROM_WriteByte(0x03ff, program_select);
}

interrupt_INTx_t int0_interrupt = {
    .EXT_InterruptHandler = int0_app_isr,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

void program1 (void){
    led_turn_off(&led2);
    led_turn_toggle(&led1);
    __delay_ms(250);
}

void program2 (void){
    led_turn_off(&led1);
    led_turn_toggle(&led2);
    __delay_ms(250);
}

Std_ReturnType ret = E_OK;
int main() {

    application_initialize();
    
    Data_EEPROM_WriteByte(0x03ff, 0);
    Data_EEPROM_ReadByte(0x03ff, &program_select); /* be careful with data you read */ 
    
    while (1) {
        if(1 == program_select){
            program1();
        }else if(2 == program_select){
            program2();
        }else{
            ret =led_turn_off(&led1);
            ret =led_turn_off(&led2);
        }
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    ret = E_NOT_OK;
    ecu_layer_intialize();
    
    ret = Interrupt_INTx_init(&int0_interrupt);
    
}