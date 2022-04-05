/*
 * AI_Digit_Common.c
 *
 *  Created on: Apr 3, 2022
 *      Author: piotr
 */

#include "AI_Digit_Common.h"

#include "app_x-cube-ai.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

AI_Digit_StateMachine process_state = IDLE;

void AI_Digit_Process(void)
{
	if(IDLE == process_state || WAIT == process_state)
	{
		return;
	}
	else if(AI_PROCESS == process_state)
	{
		MX_X_CUBE_AI_Process();
		AI_Digit_set_next_state();
	}
	else if(CLEAR_SCREEN == process_state)
	{
		LCD_Display_Init_Screen();
		AI_Digit_set_next_state();
	}
}

void AI_Digit_set_next_state(void)
{
	process_state++;

	if(CLEAR_SCREEN < process_state)
	{
		process_state = IDLE;
	}
}

void Virtual_LED_ON(uint8_t led_number)
{
	uint16_t x, y;

	x = 10;
	y = 10 + led_number * 25;

	BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
	BSP_LCD_FillRect(x, y, 20, 20);
}

void Virtual_LED_OFF(uint8_t led_number)
{
	uint16_t x, y;

	x = 10;
	y = 10 + led_number * 25;

	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(x, y, 20, 20);
}

void Virtual_LED_OFF_All()
{
	for (int i = 0; i < 10; ++i)
	{
		Virtual_LED_OFF(i);
	}
}

void scale_nearest_neighbour_algorithm(uint32_t *original_image, uint8_t *prepared_image)
{
	uint32_t ratio;
	uint32_t x,y;
	uint32_t x_offset;

	ratio = BSP_LCD_GetYSize() / 28.0;
	x_offset = BSP_LCD_GetXSize() - BSP_LCD_GetYSize();

	for(uint32_t j=0; j<28; j++)
	{
		for(uint32_t i=0; i<28; i++)
		{
			x = ratio*i;
			y = ratio*j;

			*(prepared_image + j * 28 + i) = *(original_image + (y*BSP_LCD_GetXSize() + x + x_offset)) & 0xFF;
		}
	}
}

void LCD_and_TouchScreen_Init(void)
{
	BSP_LCD_Init();
	if(BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize()) == TS_DEVICE_NOT_FOUND);
	BSP_TS_ITConfig();

	BSP_LCD_LayerDefaultInit(1, SDRAM_DEVICE_ADDR);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
}

void LCD_Display_Init_Screen(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(BSP_LCD_GetXSize() - BSP_LCD_GetYSize(), 0, BSP_LCD_GetYSize(), BSP_LCD_GetYSize());
	Virtual_LED_OFF_All();

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(50, 20, (uint8_t *)"Digit:", LEFT_MODE);
	BSP_LCD_DisplayStringAt(50, 50, (uint8_t *)"Accuracy:", LEFT_MODE);
}
