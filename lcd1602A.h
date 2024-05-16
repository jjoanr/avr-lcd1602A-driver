#ifndef _LCD1602A_H_
#define _LCD1602A_H_

// LCD commands
#define LCD_CMD_CLEAR_DISPLAY    0x01
#define LCD_CMD_RETURN_HOME      0x02
#define LCD_CMD_ENTRY_MODE_SET   0x04
#define LCD_CMD_DISPLAY_CONTROL  0x08
#define LCD_CMD_CURSOR_SHIFT     0x10
#define LCD_CMD_FUNCTION_SET     0x20
#define LCD_CMD_SET_CGRAM_ADDR   0x40
#define LCD_CMD_SET_DDRAM_ADDR   0x80

// LCD entry mode set
#define LCD_ENTRY_MODE_SHIFT_LEFT   0x03
#define LCD_ENTRY_MODE_SHIFT_RIGHT  0x02

// LCD function set options
#define LCD_FUNCTION_8BIT        0x10
#define LCD_FUNCTION_4BIT        0x00
#define LCD_FUNCTION_2LINE       0x08
#define LCD_FUNCTION_1LINE       0x00
#define LCD_FUNCTION_5x10DOTS    0x04
#define LCD_FUNCTION_5x8DOTS     0x00

// LCD display control options
#define LCD_DISPLAY_ON           0x04
#define LCD_CURSOR_ON            0x02
#define LCD_BLINK_ON             0x01

// Pin mappings, change them accordingly
#define LCD_RS PE4
#define LCD_E  PE5
#define LCD_D4 PG5
#define LCD_D5 PE3
#define LCD_D6 PH3
#define LCD_D7 PH4

/* Function prototypes */

// Initializes parameters/pins for the LCD
void lcd_init();
// Sends command to the LCD
void lcd_command(uint8_t cmd); 
//Writes a char
void lcd_write_char(char data); 
//Writes a string
void lcd_write_string(const char *str); 
// Moves cursor to specified position
void lcd_move_cursor(uint8_t row, uint8_t col);
//Sends a nibble
void lcd_send_nibble(uint8_t nibble); 

#endif /* _LCD1602A_H_ */
