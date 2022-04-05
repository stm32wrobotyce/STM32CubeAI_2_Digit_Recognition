/*
 * AI_Digit_Common.h
 *
 *  Created on: Apr 3, 2022
 *      Author: piotr
 */

#ifndef INC_AI_DIGIT_COMMON_H_
#define INC_AI_DIGIT_COMMON_H_

#include "stm32f7xx_hal.h"

typedef enum
{
	IDLE = 0,
	AI_PROCESS,
	WAIT,
	CLEAR_SCREEN
}AI_Digit_StateMachine;

void AI_Digit_Process(void);
void AI_Digit_set_next_state(void);

void Virtual_LED_ON(uint8_t led_number);
void Virtual_LED_OFF(uint8_t led_number);
void Virtual_LED_OFF_All();
void scale_nearest_neighbour_algorithm(uint32_t *original_image, uint8_t *prepared_image);

void LCD_and_TouchScreen_Init(void);
void LCD_Display_Init_Screen(void);

#endif /* INC_AI_DIGIT_COMMON_H_ */
