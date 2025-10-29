/*
 * global.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ASUS
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

/* Includes */
#include "main.h"
#include "software_timer.h"
#include "button.h"
#include "traffic_light.h"
#include "led_7seg.h"

/* Define */

// STATES OF AUTOMATIC MODE
#define INIT		1
#define RED_GREEN	2
#define RED_YELLOW	3
#define GREEN_RED	4
#define YELLOW_RED	5
// ---------------------------------

/* Variables */
extern int status;
extern int redDuration;
extern int yellowDuration;
extern int greenDuration;

#endif /* INC_GLOBAL_H_ */
