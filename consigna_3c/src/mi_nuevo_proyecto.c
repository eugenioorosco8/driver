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



/*==================[macros and definitions]=================================*/
#define MAXDELAY 800000

bool FlagCounter = 0;

/*==================[internal data declaration]==============================*/

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
	uint8_t LedSelecionado = 1;
	int8_t Periodo = 0;
		/* perform the needed initialization here */
		InicializarLeds();
		InicializarTeclas();
		InicializarTimer(250);

		while(1){
			/* Consigna 3.1 b) */
			if(LeerTecla(TECLA1)){
				delayNoelegante(MAXDELAY);
				LedSelecionado--;
				if(LedSelecionado == 0) LedSelecionado = 4;
			}
			if(LeerTecla(TECLA2)){
				delayNoelegante(MAXDELAY);
				LedSelecionado ++;
				if(LedSelecionado == 5) LedSelecionado = 1;
			}
			if(LeerTecla(TECLA3)){
				delayNoelegante(MAXDELAY);
				Periodo -=2;
				if(Periodo == -200) Periodo = -200; // SAturacion de seguridad
				InicializarTimer(250 + Periodo);
			}
			if(LeerTecla(TECLA4)){
				delayNoelegante(MAXDELAY);
				Periodo +=2;
				if(Periodo == 200) Periodo = 200; // SAturacion de seguridad
				InicializarTimer(250 + Periodo);
			}
			if (FlagCounter == 1){
				FlagCounter =0;
				switch(LedSelecionado){
				case 1:
					ToogleLed(LED0R);
					ApagaLed(LED1);
					ApagaLed(LED2);
					ApagaLed(LED3);
					ApagaLed(LED0G);
					break;
				case 2:
					ToogleLed(LED1);
					ApagaLed(LED0R);
					ApagaLed(LED2);
					ApagaLed(LED3);
					ApagaLed(LED0G);
					break;
				case 3:
					ToogleLed(LED2);
					ApagaLed(LED1);
					ApagaLed(LED0R);
					ApagaLed(LED3);
					ApagaLed(LED0G);
					break;
				case 4:
					ToogleLed(LED3);
					ApagaLed(LED1);
					ApagaLed(LED2);
					ApagaLed(LED0R);
					ApagaLed(LED0G);
					break;
				default:
					ApagaLed(LED1);
					ApagaLed(LED2);
					ApagaLed(LED3);
					ApagaLed(LED0R);
					break;
				}
			}
		}
    return 0;
}

void MyRITimerISR(void){
	FlagCounter = 1;
	Chip_RIT_ClearInt(LPC_RITIMER);

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

