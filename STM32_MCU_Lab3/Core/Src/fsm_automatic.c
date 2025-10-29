/*
 * fsm_automatic.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ASUS
 */

/* Includes */
#include "fsm_automatic.h"

/* Variables */

/* Functions */

/**
 * @brief	Run the FSM in automatic mode
 * @param	None
 * @retval	None
 */
void FSM_Automatic_Run(void) {
	switch (status) {
	case INIT:
		setAllRedLED(OFF);
		setAllYellowLED(OFF);
		setAllGreenLED(OFF);

		status = RED_GREEN;
		setTimer(1, 1000 * redDuration);
		setTimer(2, 1000 * greenDuration);
		break;

	case RED_GREEN:
		setLightWay1(RESET, SET, SET);
		setLightWay2(SET, SET, RESET);

		if (isTimerExpired(2) == 1) {
			status = RED_YELLOW;
			setTimer(2, 1000 * yellowDuration);
		}
		break;

	case RED_YELLOW:
		setLightWay1(RESET, SET, SET);
		setLightWay2(SET, RESET, SET);

		if (isTimerExpired(2) == 1) {
			status = GREEN_RED;
			setTimer(1, 1000 * greenDuration);
			setTimer(2, 1000 * redDuration);
		}
		break;

	case GREEN_RED:
		setLightWay1(SET, SET, RESET);
		setLightWay2(RESET, SET, SET);

		if (isTimerExpired(1) == 1) {
			status = YELLOW_RED;
			setTimer(1, 1000 * yellowDuration);
		}
		break;

	case YELLOW_RED:
		setLightWay1(SET, RESET, SET);
		setLightWay2(RESET, SET, SET);

		if (isTimerExpired(1) == 1) {
			status = RED_GREEN;
			setTimer(1, 1000 * redDuration);
			setTimer(2, 1000 * greenDuration);
		}
		break;

	default:
		break;
	}
}
