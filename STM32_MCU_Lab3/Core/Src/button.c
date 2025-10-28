/*
 * button.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ASUS
 */

/* Includes */
#include "button.h"

/* Variables */
GPIO_TypeDef* BTN_GPIO[MAX_BUTTON] = {
		BUTTON_1_GPIO_Port,
		BUTTON_2_GPIO_Port,
		BUTTON_3_GPIO_Port
};

uint16_t BTN_Pin[MAX_BUTTON] = {
		BUTTON_1_Pin,
		BUTTON_2_Pin,
		BUTTON_3_Pin
};

int TimeOutForKeyPress = 300;
int button_flag[MAX_BUTTON] = { 0 };
int button_long_flag[MAX_BUTTON] = { 0 };

/* Functions */

/**
 * @brief	Check if the index button is pressed or not
 * @param	index : The index of the current button
 * @retval	1 if the button is pressed (flag = 1) or 0 if it is not (flag = 0)
 */
int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

/**
 * @brief	Check if the index button is pressed and hold (for more than 3s) or not
 * @param	index : The index of current button
 * @retval	1 if the button is pressed and hold (flag = 1) or 0 if it is not (flag = 0)
 */
int isButtonLongPressed(int index) {
	if (button_long_flag[index] == 1) {
		button_long_flag[index] = 0;
		return 1;
	}
	return 0;
}

/**
 * @brief	Get the input from buttons and debounce processing
 * @param	None
 * @retval	None
 */
void getKeyInput(void) {

}
