/*
 * uartDriver.h
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

#define INT_RX 0
#define INT_TX 1

#define BAUD_9600 9600
#define BAUD_115K 115200

void InicializarUart(uint8_t);
void InicializarIntUart(uint8_t);
void SendChar(uint8_t);
void MySendString(void *, uint16_t);
uint8_t MyReceiveChar(void);


#endif /* UARTDRIVER_H_ */
