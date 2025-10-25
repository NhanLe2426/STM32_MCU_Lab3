/*
 * software_timer.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ASUS
 */

/* Includes */
#include "software_timer.h"

/* Variables */
int timer_flag[10] = { 0 };
int timer_counter[10] = { 0 };

/* Functions */

/**
 * @brief	Set duration of software timer interrupt at the index position
 * @param	index : The index of current timer
 * 			duration : Duration of software timer interrupt
 * @retval 	None
 */
void timerSet(int index, int duration) {
	timer_counter[index] = duration / TIMER_CYCLE;
	timer_flag[index] = 0;
}

/**
 * @brief	Run the timer
 * @param	None
 * @retval	None
 */
void timerRun(void) {
	for (int i = 0; i < 10; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
			if (timer_counter[i] <= 0) {
				timer_flag[i] = 1;
			}
		}
	}
}
