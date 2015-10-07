/*
 * uartDriver.c
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */

#include "chip.h"
#include "uartDriver.h"




LPC_USART_T *canal_global;

void InicializarUart(uint8_t canal){

	switch(canal){
	case 0:
		canal_global=LPC_USART0;
		Chip_SCU_PinMux(9, 5, MD_PDN, FUNC7); /* P2 3: USART3 TXD */
		Chip_SCU_PinMux(9, 6, MD_PLN|MD_EZI|MD_ZI,FUNC7); /* P2 4: USART3 RXD */
		break;
	case 2:
		canal_global=LPC_USART2;
		Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6); /* P2 3: USART3 TXD */
		Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI,FUNC6); /* P2 4: USART3 RXD */
		break;
	case 3:
		canal_global=LPC_USART3;
		Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2); /* P2 3: USART3 TXD */
		Chip_SCU_PinMux(2, 4, MD_PLN|MD_EZI|MD_ZI,FUNC2); /* P2 4: USART3 RXD */
		break;
	default:
		canal_global=LPC_USART3;
		Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2); /* P2 3: USART3 TXD */
		Chip_SCU_PinMux(2, 4, MD_PLN|MD_EZI|MD_ZI,FUNC2); /* P2 4: USART3 RXD */
		break;
	}
	Chip_UART_Init(canal_global);
	Chip_UART_SetBaud(canal_global, BAUD_115K);
	Chip_UART_SetupFIFOS(canal_global, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
	Chip_UART_TXEnable(canal_global);
}

void InicializarIntUart(uint8_t RxTx){
	NVIC_ClearPendingIRQ(USART3_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	if(RxTx == INT_RX){
		 Chip_UART_IntEnable(canal_global, UART_IER_RBRINT);
	}
	if(RxTx == INT_TX){
		 Chip_UART_IntEnable(canal_global, UART_IER_THREINT);
	}
	if(RxTx == INT_TX|INT_RX){
			 Chip_UART_IntEnable(canal_global, UART_IER_RBRINT|UART_IER_THREINT);
		}
}

void SendChar(uint8_t data){
	Chip_UART_SendByte(canal_global,data);
}

void MySendString(void *data, uint16_t numBytes){
	Chip_UART_SendBlocking(canal_global, data, numBytes);
}

void MyReceiveChar(void *data){
	Chip_UART_ReadBlocking(canal_global, data, 1);
}
