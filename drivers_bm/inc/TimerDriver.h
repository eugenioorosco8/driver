/*
 * led.h
 *
 *  Created on: 21/9/2015
 *      Author: Usuario
 */

#ifndef TIMERDRIVER_H_
#define TIMERDRIVER_H_

#include "chip.h"
#include "led.h"
#include "switch.h"

void InicializarTimer(uint8_t);

void SetBaseTimer(uint8_t);

void ClearTimer(void);

uint32_t GetTimer(void);



#endif /* LED_H_ */
