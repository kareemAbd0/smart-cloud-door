//
// Created by kareem on 3/13/24.
//

//#include "gpio.h"
#include "linux/gpio/consumer.h"
#include <linux/delay.h>
#include "lcd_platform_driver_data.h"
#include "lcd.h"



ssize_t LCD_init(struct lcd_drv_data *lcdDrvData) {



    /*set the pins to output*/

    gpiod_direction_output(lcdDrvData->gpio_devices[EN_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[RS_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[RW_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[D4_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[D5_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[D6_PIN]->desc,0);
    gpiod_direction_output(lcdDrvData->gpio_devices[D7_PIN]->desc,0);



    mdelay(25);



    /*set to 4 bit mode*/
    LCD_send_command(0x02,lcdDrvData);
    mdelay(25);
    LCD_send_command(0x28,lcdDrvData);
    mdelay(25);
    /*display on cursor blinking*/
    LCD_send_command(0x0f,lcdDrvData);
    mdelay(25);
    /*entry mode set*/
    LCD_send_command(0x06,lcdDrvData);
    mdelay(25);
    /*clear display*/
    LCD_send_command(0x01,lcdDrvData);


    return 0;

}



ssize_t LCD_send_command(unsigned char u8_command,struct lcd_drv_data * lcdDrvData ){


    gpiod_set_value( lcdDrvData->gpio_devices[RS_PIN]->desc,LOW);
    /*send the high nibble*/
    LCD_latch_data(u8_command >> 4,lcdDrvData);
    /*send the low nibble*/
    LCD_latch_data(u8_command & 0x0F ,lcdDrvData);

    return 0;

}



ssize_t LCD_display_char(const char data, struct lcd_drv_data *lcdDrvData) {
    gpiod_set_value( lcdDrvData->gpio_devices[RS_PIN]->desc,HIGH);

    /*send the high nibble*/
    LCD_latch_data(data >> 4, lcdDrvData);
    /*send the low nibble*/
    LCD_latch_data(data & 0x0F , lcdDrvData);

    return 0;
}

ssize_t LCD_display_string(const char *string, struct lcd_drv_data * lcdDrvData){

    int i = 0;
    while(string[i] != '\0'){

        /*debugging*/
        pr_info("%c ",string[i]);


        LCD_display_char(string[i], lcdDrvData);
        i++;
    }

    return 0;
}



ssize_t LCD_set_cursor(unsigned char row, unsigned char col, struct lcd_drv_data * lcdDrvData) {

    if (row == 1 ){
        LCD_send_command(0x80 + col, lcdDrvData);
    }else if(row == 2){
        LCD_send_command(0xC0 + col, lcdDrvData);
    }else{
        return -1;
    }
    return 0;
}




ssize_t LCD_latch_data(unsigned char u8_data , struct lcd_drv_data * lcdDrvData){

    gpiod_set_value( lcdDrvData->gpio_devices[RW_PIN]->desc,LOW);


    gpiod_set_value( lcdDrvData->gpio_devices[D4_PIN]->desc, (u8_data >> 0) & 0x01);
    gpiod_set_value( lcdDrvData->gpio_devices[D5_PIN]->desc, (u8_data >> 1) & 0x01);
    gpiod_set_value( lcdDrvData->gpio_devices[D6_PIN]->desc, (u8_data >> 2) & 0x01);
    gpiod_set_value( lcdDrvData->gpio_devices[D7_PIN]->desc, (u8_data >> 3) & 0x01);

    gpiod_set_value( lcdDrvData->gpio_devices[EN_PIN]->desc,HIGH);
    mdelay(10);
    gpiod_set_value( lcdDrvData->gpio_devices[EN_PIN]->desc,LOW);

    return 0;
}



ssize_t LCD_final(struct lcd_drv_data * lcdDrvData){
    gpiod_set_value( lcdDrvData->gpio_devices[RW_PIN]->desc,LOW);

    gpiod_set_value( lcdDrvData->gpio_devices[EN_PIN]->desc,LOW);

    gpiod_set_value( lcdDrvData->gpio_devices[D4_PIN]->desc,LOW);
    gpiod_set_value( lcdDrvData->gpio_devices[D5_PIN]->desc,LOW);
    gpiod_set_value( lcdDrvData->gpio_devices[D6_PIN]->desc,LOW);
    gpiod_set_value( lcdDrvData->gpio_devices[D7_PIN]->desc,LOW);

    return 0;
}




