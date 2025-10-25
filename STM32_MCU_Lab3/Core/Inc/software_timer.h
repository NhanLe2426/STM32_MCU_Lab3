/*
 * software_timer.h
 *
 *  Created on: Oct 14, 2025
 *      Author: ASUS
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

/* Includes */
#include "main.h"

/* Define */
#define TIMER_CYCLE		10

/* Variables */
extern int timer_flag[10];
extern int timer_counter[10];

/* Functions */
void timerSet(int index, int duration);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
