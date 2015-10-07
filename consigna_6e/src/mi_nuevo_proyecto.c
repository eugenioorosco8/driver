/* Copyright 2015, Eugenio Orosco
 * All rights reserved.
 *
 * This file is not part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "mi_nuevo_proyecto.h"       /* <= own header */
#include "chip.h"
#include "TimerDriver.h"
#include "AdcDriver.h"
#include "uartDriver.h"
#include "setupDriver.h"



/*==================[macros and definitions]=================================*/
#define MAXDELAY 700000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void MyRITimerISR(void);
void MyEocAdcISR(void);
/*==================[internal data definition]===============================*/
uint16_t adc_value;
bool EOCFlag = 0;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */



int main(void)
{
	char mymsg[]="Hola Mundo", data=0;
	uint8_t BufferSalida[4];
	uint32_t DatoAux = 0;
	/* perform the needed initialization here */
	InicializarCPU();
	InicializarAdc(1);
	InicializarIntAdc();
	InicializarTimer(255);
	InicializarUart(2);

	MySendString(mymsg,10);
	SendChar('\n');
	SendChar('\r');
	while(1){
		if(EOCFlag == 1){
			EOCFlag = 0;
			DatoAux = (data * 3300)/1024; //esto da en mV, trato de evitar la conversion a pf
			data = (uint16_t)DatoAux;
			BufferSalida[3] = (data/1000);
			BufferSalida[2] = (data-data/1000)/100;
			BufferSalida[1] = (data-data/1000-data/100)/10;
			BufferSalida[0] = (data) % 10;
			SendChar(BufferSalida[3]+0x30);
			SendChar('.');
			SendChar(BufferSalida[2]+0x30);
			SendChar(BufferSalida[1]+0x30);
			SendChar(BufferSalida[0]+0x30);
			SendChar('V');
			SendChar('\n');
			SendChar('\r');

		}
	}
         return 0;
}

// funcion de atenci+on de interrupcion
void MyRITimerISR(void){
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW,ADC_TRIGGERMODE_RISING);
	Chip_RIT_ClearInt(LPC_RITIMER);

}

// funcion de atenci+on de interrupcion
void MyEocAdcISR(void){
	Chip_ADC_ReadValue(LPC_ADC0, 1, &adc_value);
	EOCFlag = 1;

}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

