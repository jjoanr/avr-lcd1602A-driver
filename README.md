# AVR LCD1602A Driver

Driver for the display LCD1602A for AVR microcontrollers (specifically made for the ATmega2560).

## Overview

This repository provides a driver for interfacing the LCD1602A display module with AVR microcontrollers. The driver is specifically implemented for the ATmega2560 but can be adapted for other AVR microcontrollers with minor modifications.

## Features

- Initialization of the LCD1602A display.
- Sending commands and data to the display.
- Writing characters and strings.
- Moving the cursor to specific positions.
- 4-bit mode communication.

## Pin Configuration

The default pin mappings are configured for the ATmega2560.

| LCD pin | ATmega2560 pin  |
|---------|-----------------|
| RS      | PE4             |
| E       | PE5             |
| D4      | PG5             |
| D5      | PE3             |
| D6      | PH3             |
| D7      | PH4             |

## How to Use

1. Clone the repository:

    ```sh
    git clone https://github.com/jjoanr/avr-lcd1602A-driver.git
    ```

2. Change pin mappings for the lcd in the header file, then include it in you project:

    ```c
    #include "lcd1602A.h"
    ```

3. Initialize the LCD in your main function:

    ```c
    int main(void) {
        lcd_init();
        lcd_write_string("Hello world");
        while (1) {
            // Main loop
        }
    }
    ```

4. Compile and upload your program to the AVR microcontroller.

## Function Descriptions

- `void lcd_init()`: Initializes the LCD1602A display.
- `void lcd_command(uint8_t cmd)`: Sends a command to the LCD.
- `void lcd_write_char(char data)`: Writes a character to the LCD.
- `void lcd_write_string(const char *str)`: Writes a string to the LCD.
- `void lcd_move_cursor(uint8_t row, uint8_t col)`: Moves the cursor to a specified position.
- `void lcd_send_nibble(uint8_t nibble)`: Sends a nibble (half a byte) to the LCD (used internally in 4-bit mode).

## Example

```c
#include <avr/io.h>
#include <util/delay.h>
#include "lcd1602A.h"

int main(void) {
    lcd_init();
    lcd_write_string("hello");
    lcd_move_cursor(1, 0);
    lcd_write_string("world");
    while (1) {
        // Main loop
    }
}
