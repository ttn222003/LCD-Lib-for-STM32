#include "main.h"
#include "LCD.h"

LCD1602_4bit_t LCD1; // This create LCD, and you can create how many LCD you want

int main(void)
{
    // Init the LCD1 first
    LCD1.initLCD = LCD_init();
    // Go to the place you want
    LCD1.gotoXY = LCD_Goto_XY(5,0);
    // Print string 
    LCD1.print = LCD_print((uint8_t*)"Hello World!!!");

    while(1)
    {

    }
}