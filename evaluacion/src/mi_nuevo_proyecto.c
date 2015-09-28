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
#include "ledDriver.h"
#include "TeclasDriver.h"
#include "chip.h"
#include "TimerDriver.h"
#include "AdcDriver.h"
#include "DacDriver.h"
#include "uartDriver.h"
#include "setupDriver.h"



/*==================[macros and definitions]=================================*/
#define MAXSENIALSALIDA 3000
#define MAXDELAY 700000
/*==================[internal data declaration]==============================*/
uint16_t SenialEntrada=0;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

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
	uint8_t ganancia = 1;
	uint16_t SenialSalida=0;
	uint32_t tic=0;
	char mymsg1[]="Aumento la ganancia\r\n";
	char mymsg2[]="Disminuyo la ganancia\r\n";
	char mymsg3[]="MUTE\r\n";
	/* perform the needed initialization here */
	InicializarCPU();
	InicializarUart(2);
	InicializarAdc(1);
	InicializarIntAdc();
	InicializarDac();
	InicializarLeds();
	InicializarTeclas();
	InicializarTimer(100);
	while(1){
		if(LeerTecla(TECLA1)){
			MySendString(mymsg1,21);
			ganancia++;
			delayNoelegante(MAXDELAY);
			ToogleLed(LED0R);
		}
		if(LeerTecla(TECLA2)){
			MySendString(mymsg2,23);
			ganancia--;
			delayNoelegante(MAXDELAY);

		}
		if(LeerTecla(TECLA3)){
			MySendString(mymsg3,6);
			ganancia=0;
			ToogleLed(LED2);
			delayNoelegante(MAXDELAY);
		}
		if(LeerTecla(TECLA4)){
			ToogleLed(LED3);
			delayNoelegante(MAXDELAY);
		}
		SenialSalida= ganancia*SenialEntrada;
		if(SenialSalida > MAXSENIALSALIDA)
			SenialSalida = MAXSENIALSALIDA;
		ActualizarDac_mV(SenialSalida);


	}
    return 0;


}

void MyRITimerISR(void){
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW,ADC_TRIGGERMODE_RISING);
	Chip_RIT_ClearInt(LPC_RITIMER);

}

// funcion de atenci+on de interrupcion
void MyEocAdcISR(void){
	ToogleLed(LED1);
	Chip_ADC_ReadValue(LPC_ADC0, 1, &SenialEntrada);
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

