/*
 * AdcDriver.h
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */

#ifndef ADCCDRIVER_H_
#define ADCDRIVER_H_

#include "chip.h"


void InicializarAdc(uint8_t);
void InicializarIntAdc(void);

uint16_t AdcPolling(void);



#endif /* ADCDRIVER_H_ */
