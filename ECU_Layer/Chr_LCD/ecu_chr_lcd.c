/* 
 * File:   ecu_chr_lcd.c
 * Author: sakr3
 *
 * Created on January 1, 2024, 11:27 PM
 */

#include "ecu_chr_lcd.h"

/* ------------- helper functions declarations ----------------- */
static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd, uint8 data_command);
static Std_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *lcd, uint8 data_command);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_send_enable_signal(const chr_lcd_8bit_t *lcd);

/**
 * @brief initialize the needed GPIO pins and send initialization commands to LCD
 * @param lcd pointer to the LCD configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 l_pin_counter = 0;
        /* make all pins of LCD output and write logic low*/
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for (l_pin_counter = 0; l_pin_counter < 4; ++l_pin_counter) {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_pin_counter]));
        }
        /* initialization commands referenced to data sheet*/
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        //        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE); careful with this

        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTER_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        /* define that LCD is 4bits mode now (be careful with this) */
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START);

    }

    return ret;
}

/**
 * @brief send the commands to LCD
 * @param lcd pointer to the LCD configurations
 * @param command the command that we need to send to the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* make all RS pin logic = 0 to select instruction register */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOGIC_LOW);

        /* send higher nibble then lower nibble ( send enable signal after each one */
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_send_enable_signal(lcd);

        ret = lcd_send_4bits(lcd, command);
        ret = lcd_send_enable_signal(lcd);

    }

    return ret;
}

/**
 * @brief send char that will appears on the LCD
 * @param lcd pointer to the LCD configurations
 * @param data the data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* R/W Pin connected to the GND -> Logic (0) "Hard Wired" */
        /* Write Logic (1) to the "Register Select" Pin to select the "Data Register"  */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOGIC_HIGH);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits(lcd, data >> 4);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_send_enable_signal(lcd);
        /* Send the Data through the (4-Pins" Data lines */
        ret = lcd_send_4bits(lcd, data);
        /* Send the Enable Signal on the "E" Pin */
        ret = lcd_send_enable_signal(lcd);

    }

    return ret;
}

/**
 * @brief send char that will appears on the LCD and its position in it
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param data the data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* set cursor then send data */
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }

    return ret;
}

/**
 * @brief send string that will appears on the LCD
 * @param lcd pointer to the LCD configurations
 * @param str the string data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* iterate on the string characters and send each one of it */
        /* while ends with null termenator ( '\0' ) */
        while (*str) {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }

    }

    return ret;
}

/**
 * @brief send string that will appears on the LCD and its position in it
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param str the string data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* set cursor position then send data */
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while (*str) {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }

    return ret;
}

/**
 * @brief send custom char that will appears on the LCD and its position in it and its position in CGRAM 
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param _chr dot matrix array of custom char
 * @param mem_pos the CGRAM position of custom char
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                            const uint8 _chr[], uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 lcd_counter = 0;
        /* make address counter = CGRAM start address position + char index (0=>7) */
        ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos *8)));
        /* fill the CGRAM with with custom char data (dot matrix 5*8) */
        for (lcd_counter = 0; lcd_counter < 8; ++lcd_counter) {
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        /* display the char on the LCD */
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }

    return ret;
}

/**
 * @brief initialize the needed GPIO pins and send initialization commands to LCD
 * @param lcd pointer to the LCD configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 l_pin_counter = 0;
        /* make all pins of LCD output and write logic low*/
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter) {
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_pin_counter]));
        }
        /* initialization commands referenced to data sheet*/
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);

        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTER_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START);

    }

    return ret;
}

/**
 * @brief send the commands to LCD
 * @param lcd pointer to the LCD configurations
 * @param command the command that we need to send to the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* make all RS pin logic = 0 to select instruction register */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOGIC_LOW);

        ret = lcd_send_8bits(lcd, command);
        ret = lcd_send_enable_signal(lcd);

    }

    return ret;
}

/**
 * @brief send char that will appears on the LCD
 * @param lcd pointer to the LCD configurations
 * @param data the data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* make all RS pin logic = 1 to select data register */
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOGIC_HIGH);

        ret = lcd_send_8bits(lcd, data);
        ret = lcd_send_enable_signal(lcd);

    }

    return ret;
}

/**
 * @brief send char that will appears on the LCD and its position in it
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param data the data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* set cursor position then send data */
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }

    return ret;
}

/**
 * @brief send string that will appears on the LCD
 * @param lcd pointer to the LCD configurations
 * @param str the string data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* iterate on the string characters and send each one of it */
        /* while ends with null termenator ( '\0' ) */
        while (*str) {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }

    }

    return ret;
}

/**
 * @brief send string that will appears on the LCD and its position in it
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param str the string data that will appears on the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* set cursor position then send data */
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while (*str) {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }

    return ret;
}

/**
 * @brief send custom char that will appears on the LCD and its position in it and its position in CGRAM 
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @param _chr dot matrix array of custom char
 * @param mem_pos the CGRAM position of custom char
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                            const uint8 _chr[], uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 lcd_counter = 0;
        /* make address counter = CGRAM start address position + char index (0=>7) */
        ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos *8)));
        /* fill the CGRAM with with custom char data (dot matrix 5*8) */
        for (lcd_counter = 0; lcd_counter < 8; ++lcd_counter) {
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        /* display the char on the LCD */
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
        
    }

    return ret;
}

/* ------------- integers to string conversion functions ----------------- */

/**
 * @brief convert 8 bit integer to string
 * @param value the integer value that will converted 
 * @param str the result of conversion 
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str) {
    Std_ReturnType ret = E_OK;
    uint8 TempString[4] = {0};
    uint8 DataCounter = 0;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, ' ', 3);
        str[3] = '\0';
        sprintf((char *)TempString, "%i", value);
        while(TempString[DataCounter] != '\0'){
            str[DataCounter] = TempString[DataCounter];
            DataCounter++;
        }
    }

    return ret;
}

/**
 * @brief convert 16 bit integer to string
 * @param value the integer value that will converted 
 * @param str the result of conversion 
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str) {
    Std_ReturnType ret = E_OK;
    uint8 TempString[6] = {0};
    uint8 DataCounter = 0;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, ' ', 5);
        /* Make Last char in string = null*/
        str[5] = '\0';
        sprintf((char *)TempString, "%i", value);
        /* Take the digits without null termination */
        while(TempString[DataCounter] != '\0'){
            str[DataCounter] = TempString[DataCounter];
            DataCounter++;
        }
    }

    return ret;
}

/**
 * @brief convert 32 bit integer to string
 * @param value the integer value that will converted 
 * @param str the result of conversion 
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str) {
    Std_ReturnType ret = E_OK;
    uint8 TempString[11] = {0};
    uint8 DataCounter = 0;
    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str, ' ', 10);
        str[10] = '\0';
        sprintf((char *)TempString, "%i", value);
        /* Take the digits without null termination */
        while(TempString[DataCounter] != '\0'){
            str[DataCounter] = TempString[DataCounter];
            DataCounter++;
        }
    }

    return ret;
}

/* ------------- helper functions ----------------- */

/**
 * @brief send data or command to 4 bit LCD
 * @param lcd pointer to the LCD configurations
 * @param data_command the data that we need to send to the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd, uint8 data_command) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 l_pin_counter = 0;
        /* write the logic of command in data pins */
        for (l_pin_counter = 0; l_pin_counter < 4; ++l_pin_counter) {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), READ_BIT(data_command, l_pin_counter));
        }
    }

    return ret;
}

/**
 * @brief send data or command to 8 bit LCD
 * @param lcd pointer to the LCD configurations
 * @param data_command the data that we need to send to the LCD
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *lcd, uint8 data_command) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        uint8 l_pin_counter = 0;
        /* write the logic of command in data pins */
        for (l_pin_counter = 0; l_pin_counter < 8; ++l_pin_counter) {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_pin_counter]), READ_BIT(data_command, l_pin_counter));
        }
    }

    return ret;
}

/**
 * @brief set cursor in one of LCD positions 
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* columns start from 0 */
        column--;
        switch (row) {
            case ROW1: lcd_4bit_send_command(lcd, (0x80 + column));
                break;
            case ROW2: lcd_4bit_send_command(lcd, (0xc0 + column));
                break;
            case ROW3: lcd_4bit_send_command(lcd, (0x94 + column));
                break;
            case ROW4: lcd_4bit_send_command(lcd, (0xd4 + column));
                break;
            default: break;
        }
    }

    return ret;
}

/**
 * @brief set cursor in one of LCD positions 
 * @param lcd pointer to the LCD configurations
 * @param row the row position which the cursor set on it
 * @param column the column position which the cursor set on it
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* columns start from 0 */
        column--;
        switch (row) {
            case ROW1: lcd_8bit_send_command(lcd, (0x80 + column));
                break;
            case ROW2: lcd_8bit_send_command(lcd, (0xc0 + column));
                break;
            case ROW3: lcd_8bit_send_command(lcd, (0x94 + column));
                break;
            case ROW4: lcd_8bit_send_command(lcd, (0xd4 + column));
                break;
            default: break;
        }
    }

    return ret;
}

/**
 * @brief send enable signal which comment the changes
 * @param lcd pointer to the LCD configurations
 * @return status of the function
 *          ( E_OK ): the function done successfully 
 *          ( E_NOT_OK ): the function has issue to perform this action
 */
static Std_ReturnType lcd_send_enable_signal(const chr_lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        /* make enable signal ( falling edge ) */
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOGIC_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOGIC_LOW);
    }

    return ret;
}

