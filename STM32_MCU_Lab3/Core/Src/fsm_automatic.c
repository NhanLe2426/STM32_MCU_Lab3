/*
 * fsm_automatic.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ASUS
 */

/* Includes */
#include "fsm_automatic.h"

/* Variables */
int index_led = 0;

/* Functions */

/**
 * @brief	Run the FSM in automatic mode
 * @param	None
 * @retval	None
 */
void FSM_Automatic_Run(void) {
	switch (status) {
	case INIT_AUTO:
		setAllRedLED(OFF);
		setAllYellowLED(OFF);
		setAllGreenLED(OFF);

		status = RED_GREEN;
		setTimer(0, 5000);
		setTimer(1, 1000 * redDuration);
		setTimer(2, 1000 * greenDuration);

		button_flag[0] = 0;
		button_flag[1] = 0;
		button_flag[2] = 0;

		updateLedBuffer(0, (redDuration) / 10);
		updateLedBuffer(1, (redDuration) % 10);
		updateLedBuffer(2, (greenDuration) / 10);
		updateLedBuffer(3, (greenDuration) % 10);
		break;

	case RED_GREEN:
		setLightWay1(RESET, SET, SET);
		setLightWay2(SET, SET, RESET);

		if (isTimerExpired(2) == 1) {
			status = RED_YELLOW;
			setTimer(2, 1000 * yellowDuration);

			updateLedBuffer(2, (yellowDuration) / 10);
			updateLedBuffer(3, (yellowDuration) % 10);
		}

		// Press button 3 to access MANUAL MODE
		if (isButtonPressed(2) == 1) {
			status = INIT_MAN;
		}
		break;

	case RED_YELLOW:
		setLightWay1(RESET, SET, SET);
		setLightWay2(SET, RESET, SET);

		if (isTimerExpired(2) == 1) {
			status = GREEN_RED;
			setTimer(1, 1000 * greenDuration);
			setTimer(2, 1000 * redDuration);

			updateLedBuffer(0, (greenDuration) / 10);
			updateLedBuffer(1, (greenDuration) % 10);
			updateLedBuffer(2, (redDuration) / 10);
			updateLedBuffer(3, (redDuration) % 10);
		}

		// Press button 3 to access MANUAL MODE
		if (isButtonPressed(2) == 1) {
			status = INIT_MAN;
		}
		break;

	case GREEN_RED:
		setLightWay1(SET, SET, RESET);
		setLightWay2(RESET, SET, SET);

		if (isTimerExpired(1) == 1) {
			status = YELLOW_RED;
			setTimer(1, 1000 * yellowDuration);

			updateLedBuffer(0, (yellowDuration) / 10);
			updateLedBuffer(1, (yellowDuration) % 10);
		}

		// Press button 3 to access MANUAL MODE
		if (isButtonPressed(2) == 1) {
			status = INIT_MAN;
		}
		break;

	case YELLOW_RED:
		setLightWay1(SET, RESET, SET);
		setLightWay2(RESET, SET, SET);

		if (isTimerExpired(1) == 1) {
			status = RED_GREEN;
			setTimer(1, 1000 * redDuration);
			setTimer(2, 1000 * greenDuration);

			updateLedBuffer(0, (redDuration) / 10);
			updateLedBuffer(1, (redDuration) % 10);
			updateLedBuffer(2, (greenDuration) / 10);
			updateLedBuffer(3, (greenDuration) % 10);
		}

		// Press button 3 to access MANUAL MODE
		if (isButtonPressed(2) == 1) {
			status = INIT_MAN;
		}
		break;

	default:
		break;
	}

	if (status != INIT_AUTO) {
		// Scan 4 7-segment LEDs with the frequency of 0.5Hz
		if (isTimerExpired(3) == 1) {
			update7SEG(index_led++);
			index_led = index_led % 4;
			setTimer(3, 500);
		}

		// Count down the duration for displaying on 7-segment LEDs
		if (isTimerExpired(4) == 1) {
			updateLedBuffer(1, led_buffer[1] - 1);
			updateLedBuffer(3, led_buffer[3] - 1);
			setTimer(4, 1000);
		}
	}
}
