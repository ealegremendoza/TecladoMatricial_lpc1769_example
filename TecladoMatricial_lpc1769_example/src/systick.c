/*
 * systick.c
 *
 *  Created on: 19 mar. 2021
 *      Author: ealegremendoza
 */
#include "systick.h"

void SysTick_Init(uint32_t frecuencia)
{
	uint32_t Temporal=0;
	if(frecuencia > 0xffffff)
		return;
	Temporal=CCLK/frecuencia - 1;
	STCURR = 0;
	STRELOAD = Temporal;
	STCTRL = (1<<0)|(1<<1)|(1<<2);
}
void SysTick_Handler(void)
{
	// Here every 1ms.
	static uint32_t Divisor_100ms = 0;
	Divisor_100ms++;
	if(Divisor_100ms==100)
	{
		Divisor_100ms=0;
		TECLADO_Antirebote();
		//TECLADO_Antirebote_Mantiene_Tecla();
	}
}
