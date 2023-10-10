#ifndef	__LCD_H__
#define __LCD_H__
#include "main.h"
// Define type of LCD
#define LCD1602	0
//#define	LCD2004	1

/****************** define Port *******************/
#define RS_PORT	GPIOB
#define RW_PORT	GPIOB
#define EN_PORT	GPIOB
#define D4_PORT	GPIOB
#define D5_PORT	GPIOB
#define D6_PORT	GPIOB
#define D7_PORT	GPIOB
/****************** define Pin ********************/
#define RS_PIN	GPIO_PIN_8
#define RW_PIN	GPIO_PIN_9
#define EN_PIN	GPIO_PIN_10
#define D4_PIN	GPIO_PIN_4
#define D5_PIN	GPIO_PIN_5
#define D6_PIN	GPIO_PIN_6
#define D7_PIN	GPIO_PIN_7
/**************************************************/
typedef struct{
	uint8_t initLCD;
	uint8_t print;
	uint8_t gotoXY;
	uint8_t clear;
	uint8_t returnHome;
}LCD1602_4bit_t;

void Put4bits (int put_data);
void LCD_put (int put_data);
uint8_t LCD_init (void);
uint8_t LCD_print(uint8_t* str);
uint8_t LCD_Goto_XY (int x, int y);
uint8_t LCD_Clear(void);
uint8_t LCD_ReturnHome (void);
uint8_t LCD_Create_Special_Character (uint8_t* special_character, uint8_t pattern_position);
#endif
