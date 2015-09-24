/*
 * led.h
 *
 *  Created on: 21/9/2015
 *      Author: Usuario
 */

#ifndef ADCCDRIVER_H_
#define ADCDRIVER_H_

#include "chip.h"


void InicializarAdc(uint8_t);
void InicializarIntAdc(void);

uint16_t AdcPolling(void);



#endif /* LED_H_ */
