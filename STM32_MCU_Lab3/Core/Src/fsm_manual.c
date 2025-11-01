/*
 * fsm_manual.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ASUS
 */

/* Includes */
#include "fsm_manual.h"

/* Variables */
int initCounter = 5;
int modeCounter = 5;

/* Functions */
void FSM_Manual_Run(void) {
	switch (status) {
	case INIT_MAN:
		setAllRedLED(OFF);
		setAllYellowLED(OFF);
		setAllGreenLED(OFF);

		setTimer(6, 1000 * modeCounter);

		// Press button 1 to access RED_GREEN_MAN mode
		if (isButtonPressed(0) == 1) {
			status = RED_GREEN_MAN;
		}
		// Press button 2 to access GREEN_RED_MAN mode
		if (isButtonPressed(1) == 1) {
			status = GREEN_RED_MAN;
		}
		// Count down for 3s, if no buttons are pressed, return to AUTO MODE
		if (isTimerExpired(0) == 1) {
			status = INIT_AUTO;
			setTimer(0, 1000 * initCounter);

//			updateLedBuffer(0, 0);
//			updateLedBuffer(1, 0);
//			updateLedBuffer(2, 0);
//			updateLedBuffer(3, 0);
		}
		break;

	case RED_GREEN_MAN:
		setLightWay1(RESET, SET, SET);
		setLightWay2(SET, SET, RESET);

		// Press button 2 to access GREEN_RED_MAN mode
		if (isButtonPressed(1) == 1) {
			status = GREEN_RED_MAN;
		}

		// Press and hold button 1 to return to AUTO MODE
		if (isButtonLongPressed(0) == 1) {
			status = INIT_AUTO;
		}

		// Count down for 10s, if no buttons are pressed, return to AUTO MODE
		if (isTimerExpired(6) == 1) {
			status = INIT_AUTO;
			setTimer(6, 1000 * modeCounter);

			updateLedBuffer(0, modeCounter / 10);
			updateLedBuffer(1, modeCounter % 10);
			updateLedBuffer(2, modeCounter / 10);
			updateLedBuffer(3, modeCounter % 10);
		}
		break;

	case GREEN_RED_MAN:
		setLightWay1(SET, SET, RESET);
		setLightWay2(RESET, SET, SET);

		// Press button 1 to access RED_GREEN_MAN mode
		if (isButtonPressed(0) == 1) {
			status = RED_GREEN_MAN;
		}
		// Press and hold button 2 to return to AUTO MODE
		if ((isButtonLongPressed(1) == 1) || (isTimerExpired(6) == 1)) {
			status = INIT_AUTO;
		}

		// Count down for 10s, if no buttons are pressed, return to AUTO MODE
		if (isTimerExpired(6) == 1) {
			status = INIT_AUTO;
			setTimer(6, 1000 * modeCounter);

			updateLedBuffer(0, modeCounter / 10);
			updateLedBuffer(1, modeCounter % 10);
			updateLedBuffer(2, modeCounter / 10);
			updateLedBuffer(3, modeCounter % 10);
		}
		break;

	default:
		break;
	}
	if (status != INIT_MAN) {
		// Scan 4 7-segment LEDs with the frequency of 0.5Hz
		if (isTimerExpired(3) == 1) {
			update7SEG(index_led++);
			index_led = index_led % 4;
			setTimer(3, 500);
		}

		// Count down the duration for displaying on 7-segment LEDs
		if (isTimerExpired(4) == 1) {
			updateLedBuffer(0, led_buffer[0] - 1);
			updateLedBuffer(1, led_buffer[1] - 1);
			updateLedBuffer(2, led_buffer[2] - 1);
			updateLedBuffer(3, led_buffer[3] - 1);
			setTimer(4, 1000);
		}
	}
}
