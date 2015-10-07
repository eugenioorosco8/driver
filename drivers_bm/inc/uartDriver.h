/*
 * uartDriver.h
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */

#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_

#define INT_RX 1
#define INT_TX 2

#define BAUD_9600 9600
#define BAUD_115K 115200

void InicializarUart(uint8_t);
void InicializarIntUart(uint8_t);
void SendChar(uint8_t);
void MySendString(void *, uint16_t);
void MyReceiveChar(void *data);


#endif /* UARTDRIVER_H_ */
