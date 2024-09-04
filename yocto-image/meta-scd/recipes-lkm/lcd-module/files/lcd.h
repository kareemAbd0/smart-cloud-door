//
// Created by kareem on 3/13/24.
//

#ifndef PLATFORM_MPCHAR_LCD_H
#define PLATFORM_MPCHAR_LCD_H

// 4 bit mode


#define EN_PIN 0
#define RS_PIN 1
#define RW_PIN 2
#define D4_PIN 3
#define D5_PIN 4
#define D6_PIN 5
#define D7_PIN 6

#define LOW 0
#define HIGH 1



struct lcd_drv_data;


ssize_t LCD_init(struct lcd_drv_data * lcdDrvData);
ssize_t LCD_send_command(unsigned char u8_command,struct lcd_drv_data * lcdDrvData );
ssize_t LCD_display_char(const char data, struct lcd_drv_data *lcdDrvData);
ssize_t LCD_display_string(const char *string, struct lcd_drv_data * lcdDrvData);
ssize_t LCD_set_cursor(unsigned char row, unsigned char col, struct lcd_drv_data * lcdDrvData);
ssize_t LCD_latch_data(unsigned char u8_data ,struct lcd_drv_data * lcdDrvData);
ssize_t LCD_final(struct lcd_drv_data * lcdDrvData);

#endif //PLATFORM_MPCHAR_LCD_H
