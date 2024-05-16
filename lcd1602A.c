#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdbool.h>
#include "lcd1602A.h"

/* Initializes the LCD */
void lcd_init() {
    // Set data direction registers
    DDRE |= (1 << LCD_RS) | (1 << LCD_E) | (1 << LCD_D5);
    DDRG |= (1 << LCD_D4);
    DDRH |= (1 << LCD_D6) | (1 << LCD_D7);

    // Wait for LCD to power up, recommended > 15ms
    _delay_ms(50);

    // Initialization sequence (from manufacturer datasheet)
    // https://www.waveshare.com/datasheet/LCD_en_PDF/LCD1602.pdf

    // Step 1: Function set (Interface is 8 bits length)
    lcd_send_nibble(0x03);
    _delay_ms(5); // Wait time > 4.1 ms

    // Step 2: Function set (Interface is 8 bits length)
    lcd_send_nibble(0x03);
    _delay_us(150); // Wait time > 100 us

    // Step 3: Function set (Interface is 8 bits length)
    lcd_send_nibble(0x03);
    _delay_us(150); // Wait time > 100 us

    // Step 4: Function set (Set interface to be 4 bits length)
    lcd_send_nibble(0x02);

    // Step 5: Function set (Interface is 4 bits length, specify number of display lines and character font)
    lcd_command(LCD_CMD_FUNCTION_SET | LCD_FUNCTION_4BIT | LCD_FUNCTION_2LINE | LCD_FUNCTION_5x8DOTS);

    // Step 6: Display off
    lcd_command(LCD_CMD_DISPLAY_CONTROL);

    // Step 7: Clear display
    lcd_command(LCD_CMD_CLEAR_DISPLAY);
    _delay_ms(2); //Wait for the clear to happen (doesn't work without a delay)

    // Step 8: Entry mode set (Increment mode)
    lcd_command(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_MODE_SHIFT_RIGHT);

    // Step 9: Display on (Display on, cursor off, blink off)
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON);
}

/* Sends command to the LCD */
void lcd_command(uint8_t cmd) {
    // Set RS to 0 for command mode
    PORTE &= ~(1 << LCD_RS);

    // Send higher nibble
    lcd_send_nibble(cmd >> 4);

    // Send lower nibble
    lcd_send_nibble(cmd);

    // Small delay
    _delay_us(100);
}

/* Sends a char to write to the LCD */
void lcd_write_char(char data) {
    // Set RS to 1 for data mode
    PORTE |= (1 << LCD_RS);

    // Send higher nibble
    lcd_send_nibble(data >> 4);

    // Send lower nibble
    lcd_send_nibble(data);

    // Small delay
    _delay_us(100);
}

/* Sends a string to write to the LCD */
void lcd_write_string(const char *str) {
    while (*str) {
        lcd_write_char(*str++);
    }
}

/* Moves cursor (writing position) */
void lcd_move_cursor(uint8_t row, uint8_t col) {
    uint8_t address;

    switch(row) {
        case 0:
            address = col;
            break;
        case 1:
            address = col + 0x40;
            break;
        default:
            address = 0;
            break;
    }
    lcd_command(LCD_CMD_SET_DDRAM_ADDR | address);
}

/* Sends nibble (half a byte) to the LCD. Necessary in 4-bit mode */
void lcd_send_nibble(uint8_t nibble) {
    // Set data pins
    if (nibble & 0x01) PORTG |= (1 << LCD_D4); else PORTG &= ~(1 << LCD_D4);
    if (nibble & 0x02) PORTE |= (1 << LCD_D5); else PORTE &= ~(1 << LCD_D5);
    if (nibble & 0x04) PORTH |= (1 << LCD_D6); else PORTH &= ~(1 << LCD_D6);
    if (nibble & 0x08) PORTH |= (1 << LCD_D7); else PORTH &= ~(1 << LCD_D7);

    // Enable pulse (enable E, delay, disable E)
    PORTE |= (1 << LCD_E);
    _delay_us(1);
    PORTE &= ~(1 << LCD_E);
    _delay_us(100);
}
