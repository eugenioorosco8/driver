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



/*==================[macros and definitions]=================================*/
#define MAXDELAY 700000
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void MyRITimerISR(void);
void MyEocAdcISR(void);
/*==================[internal data definition]===============================*/
uint16_t adc_value;
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
	uint16_t UmbralBajo = 90, UmbralAlto = 900;
	/* perform the needed initialization here */
	InicializarCPU();
	InicializarAdc(1);
	InicializarIntAdc();
	InicializarLeds();
	InicializarTimer(100);

	while(1){
		/* Consigna 5.1
		adc_value=AdcPolling();
		ApagaLed(LED1);
		ApagaLed(LED2);
		if(adc_value<50)  PrenderLed(LED1);
		if(adc_value>900) PrenderLed(LED2);
		*/
		// Consigna 5,2
		if(LeerTecla(TECLA1)){
				delayNoelegante(MAXDELAY);
				UmbralBajo++;
				if(UmbralBajo > 1024) UmbralBajo = 1024;
			}
			if(LeerTecla(TECLA2)){
				delayNoelegante(MAXDELAY);
				UmbralBajo--;
				if(UmbralBajo < 0) UmbralBajo = 0;
			}
			if(LeerTecla(TECLA3)){
				delayNoelegante(MAXDELAY);
				UmbralAlto++;
				if(UmbralAlto < 1024) UmbralAlto = 1024;
			}
			if(LeerTecla(TECLA4)){
				delayNoelegante(MAXDELAY);
				UmbralAlto--;
				if(UmbralAlto < 0) UmbralAlto = 0;
			}
			;
			if(adc_value<UmbralBajo) PrenderLed(LED1);
			if(adc_value>UmbralAlto) PrenderLed(LED2);
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
}
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

