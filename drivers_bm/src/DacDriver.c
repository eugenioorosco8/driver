/*
 * DacDriver.c
 *
 *  Created on: 21/9/2015
 *      Author: Eugenio Orosco
 */
#include "chip.h"
#include "DacDriver.h"
#include "TimerDriver.h"


uint16_t amplitude_max,period_max,rate_max;

void InicializarDac(void){
	Chip_SCU_DAC_Analog_Config();
	Chip_DAC_Init(LPC_DAC);
	Chip_DAC_ConfigDAConverterControl(LPC_DAC, DAC_DMA_ENA);
	Chip_DAC_UpdateValue(LPC_DAC, 0); //0->0V -- 1024->3.3V
	amplitude_max=0;
	period_max=0;

}

void ActualizarDac_mV(uint16_t DacValue_mV){
	//0->0V -- 1024->3300mV
	uint16_t DacValue=0;
	DacValue=DacValue_mV/3;
	Chip_DAC_UpdateValue(LPC_DAC, DacValue);
}

void TriangSet(uint16_t amplitude,uint16_t period){
	amplitude_max=amplitude;
	period_max=period;
	rate_max = amplitude_max / period_max;
	ClearTimer();
}

void TriangActualiza(void){
	static uint32_t TimerValue_old;
	static uint16_t value_tmp;
	uint32_t TimerValue = GetTimer();
	if(TimerValue_old != TimerValue){  //Esta condicion permite usarlo por pulling o interrupcion
		value_tmp = rate_max * TimerValue;
		ActualizarDac_mV(value_tmp);
	}
	if(TimerValue == period_max){
		ClearTimer();
	}


}
