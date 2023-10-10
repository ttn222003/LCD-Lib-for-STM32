#include "LCD.h"
void Put4bits (int put_data){
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D7_PORT,D7_PIN,(GPIO_PinState)(put_data & 0x80));
	HAL_GPIO_WritePin(D6_PORT,D6_PIN,(GPIO_PinState)(put_data & 0x40));
	HAL_GPIO_WritePin(D5_PORT,D5_PIN,(GPIO_PinState)(put_data & 0x20));
	HAL_GPIO_WritePin(D4_PORT,D4_PIN,(GPIO_PinState)(put_data & 0x10));
	HAL_GPIO_WritePin(EN_PORT,EN_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN_PORT,EN_PIN,GPIO_PIN_RESET);
}

void LCD_put (int put_data){
	Put4bits(put_data);
	Put4bits(put_data << 4);
	HAL_Delay(1);
}

uint8_t LCD_init (void){
	HAL_Delay(15);
	HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	Put4bits(0x30);
	HAL_Delay(5);
	Put4bits(0x30);
	HAL_Delay(1);
	Put4bits(0x30);
	HAL_Delay(1);
	Put4bits(0x20);
	
	LCD_put(0x28);
	LCD_put(0x08);
	LCD_put(0x01);
	LCD_put(0x06);
	LCD_put(0x0D);
	
	return 1;
}

uint8_t LCD_print(uint8_t* str){
	HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_SET);
	int i = 0;
	while(*(str + i) != '\0'){
		LCD_put(*(str + i));
		i++;
	}
	
	return 1;
}

uint8_t LCD_Goto_XY (int x, int y){ // First row: x = 0
	int location;
	HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	#ifdef LCD1602
		location = 0x80 + 0x40 * y + x;
	#endif
	
	#ifdef LCD2004
		if((y >= 0) && (y < 2))				location = 0x80 + 0x40 * y + (x + 0);
		else if((y >= 2) && (y < 4))	location = 0x80 + 0x40 * (y - 2) + (x + 20);
	#endif
	LCD_put(location);
	
	return 1;
}

uint8_t LCD_Clear(void){
	HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	LCD_put(0x01);
	HAL_Delay(1);
	
	return 1;
}

uint8_t LCD_ReturnHome (void){
	HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	LCD_put(0x02);
	HAL_Delay(2);
	
	return 1;
}

uint8_t LCD_Create_Special_Character (uint8_t* special_character, uint8_t pattern_position){
	HAL_GPIO_WritePin(RW_PORT,RW_PIN,GPIO_PIN_RESET);
	for (uint8_t row = 0; row<8; row++){
		HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_RESET);
		LCD_put(0x40 + (pattern_position << 3) + row);
		HAL_GPIO_WritePin(RS_PORT,RS_PIN,GPIO_PIN_SET);
		LCD_put(*(special_character + row));
	}
	return 1;
}
