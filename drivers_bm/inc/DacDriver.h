/*
 * led.h
 *
 *  Created on: 21/9/2015
 *      Author: Usuario
 */

#ifndef DACDRIVER_H_
#define DACDRIVER_H_

#define CHANNEL0 1


#include "chip.h"

void InicializarDac(void);
void ActualizarDac_mV(uint16_t);

void TriangSet(uint16_t amplitude,uint16_t period);
void TriangActualiza(void);



#endif /* LED_H_ */
