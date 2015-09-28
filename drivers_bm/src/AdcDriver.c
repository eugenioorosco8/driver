/*
 * AdcDriver.c
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */
#include "chip.h"
#include "AdcDriver.h"
#include "TimerDriver.h"


uint8_t channel_global;

void InicializarAdc(uint8_t channel){
	ADC_CLOCK_SETUP_T MyADCSetup;
	MyADCSetup.adcRate = ADC_MAX_SAMPLE_RATE;
	MyADCSetup.bitsAccuracy = ADC_10BITS;
	MyADCSetup.burstMode = false;

	switch (channel){
	case 1:
		channel_global = ADC_CH1;
		break;
	case 2:
		channel_global = ADC_CH2;
		break;
	case 3:
		channel_global = ADC_CH3;
		break;
	default:
		channel_global = ADC_CH1;
		break;
	}
	Chip_SCU_ADC_Channel_Config(0, channel_global);//0 ADC0
	Chip_ADC_Init(LPC_ADC0, &MyADCSetup );
	Chip_ADC_EnableChannel(LPC_ADC0, channel_global, ENABLE);

}
void InicializarIntAdc(void){
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, channel_global, ENABLE);
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW,ADC_TRIGGERMODE_RISING);
}

uint16_t AdcPolling(void){
	uint16_t data;
	Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW,ADC_TRIGGERMODE_RISING);
	while(Chip_ADC_ReadStatus(LPC_ADC0, channel_global, ADC_DR_DONE_STAT) == RESET);
	Chip_ADC_ReadValue(LPC_ADC0, channel_global, &data);
	return data;
}




