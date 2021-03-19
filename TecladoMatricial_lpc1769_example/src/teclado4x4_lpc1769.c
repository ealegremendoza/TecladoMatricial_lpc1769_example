/*
 * Teclado4x4_lpc1769.c
 *
 *  Created on: 19 mar. 2021
 *      Author: ealegremendoza
 */

#include "teclado4x4_lpc1769.h"

uint8_t codigo_actual;
uint8_t codigo_anterior;
uint8_t codigo_valido;
uint8_t contador;

/*	fifo para teclado	*/
uint8_t IndiceIn=0;
uint8_t IndiceOut=0;
uint8_t Buffer_teclado[TAMANIO_BUFFER_TECLADO];

void TECLADO_Init(void)
{
	contador=0;
	codigo_anterior=NO_KEY;
	codigo_valido=NO_KEY;
	/*	Seteo los pines que controlan las filas como SALIDAS	*/
	/*	Nota1: Poner Diodos para proteger el micro en caso de que
	 * 			se presionen dos o más teclas a la vez.
	 * 			*/
	/*	Nota2: El cátodo del diodo se conecta al pin del micro ya que
	 * 			tengo un pull-up del otro lado. Se activa con 0.
	 * 			*/
	GPIO_Func(PIN_TECLADO_FIL0,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_FIL1,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_FIL2,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_FIL3,TECLADO_PIN_FUNC);
	GPIO_Dir(PIN_TECLADO_FIL0,TECLADO_FIL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_FIL1,TECLADO_FIL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_FIL2,TECLADO_FIL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_FIL3,TECLADO_FIL_PIN_DIR);
	GPIO_Mode(PIN_TECLADO_FIL0,TECLADO_FIL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_FIL1,TECLADO_FIL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_FIL2,TECLADO_FIL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_FIL3,TECLADO_FIL_PIN_MODE);

	/*	Seteo los pines que controlan las filas como ENTRADAS	*/
	/*	Nota: Poner las entradas con un pull-up	*/
	GPIO_Func(PIN_TECLADO_COL0,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_COL1,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_COL2,TECLADO_PIN_FUNC);
	GPIO_Func(PIN_TECLADO_COL3,TECLADO_PIN_FUNC);
	GPIO_Dir(PIN_TECLADO_COL0,TECLADO_COL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_COL1,TECLADO_COL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_COL2,TECLADO_COL_PIN_DIR);
	GPIO_Dir(PIN_TECLADO_COL3,TECLADO_COL_PIN_DIR);
	GPIO_Mode(PIN_TECLADO_COL0,TECLADO_COL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_COL1,TECLADO_COL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_COL2,TECLADO_COL_PIN_MODE);
	GPIO_Mode(PIN_TECLADO_COL3,TECLADO_COL_PIN_MODE);
}

uint8_t TECLADO_Leer_HW(void)
{
	/*	Reviso fila 0	*/
	//	Escribo donde están los diodos
	GPIO_Set(PIN_TECLADO_FIL0,0);
	GPIO_Set(PIN_TECLADO_FIL1,1);
	GPIO_Set(PIN_TECLADO_FIL2,1);
	GPIO_Set(PIN_TECLADO_FIL3,1);
	//	Leo donde no están los diodos
	if(0==GPIO_Get(PIN_TECLADO_COL0))
		return CODIGO_1;
	if(0==GPIO_Get(PIN_TECLADO_COL1))
		return CODIGO_2;
	if(0==GPIO_Get(PIN_TECLADO_COL2))
		return CODIGO_3;
	if(0==GPIO_Get(PIN_TECLADO_COL3))
		return CODIGO_A;

	/*	Reviso fila 1	*/
	//	Escribo donde están los diodos
	GPIO_Set(PIN_TECLADO_FIL0,1);
	GPIO_Set(PIN_TECLADO_FIL1,0);
	GPIO_Set(PIN_TECLADO_FIL2,1);
	GPIO_Set(PIN_TECLADO_FIL3,1);
	//	Leo donde no están los diodos
	if(0==GPIO_Get(PIN_TECLADO_COL0))
		return CODIGO_4;
	if(0==GPIO_Get(PIN_TECLADO_COL1))
		return CODIGO_5;
	if(0==GPIO_Get(PIN_TECLADO_COL2))
		return CODIGO_6;
	if(0==GPIO_Get(PIN_TECLADO_COL3))
		return CODIGO_B;

	/*	Reviso fila 2	*/
	//	Escribo donde están los diodos
	GPIO_Set(PIN_TECLADO_FIL0,1);
	GPIO_Set(PIN_TECLADO_FIL1,1);
	GPIO_Set(PIN_TECLADO_FIL2,0);
	GPIO_Set(PIN_TECLADO_FIL3,1);
	//	Leo donde no están los diodos
	if(0==GPIO_Get(PIN_TECLADO_COL0))
		return CODIGO_7;
	if(0==GPIO_Get(PIN_TECLADO_COL1))
		return CODIGO_8;
	if(0==GPIO_Get(PIN_TECLADO_COL2))
		return CODIGO_9;
	if(0==GPIO_Get(PIN_TECLADO_COL3))
		return CODIGO_C;

	/*	Reviso fila 3	*/
	//	Escribo donde están los diodos
	GPIO_Set(PIN_TECLADO_FIL0,1);
	GPIO_Set(PIN_TECLADO_FIL1,1);
	GPIO_Set(PIN_TECLADO_FIL2,1);
	GPIO_Set(PIN_TECLADO_FIL3,0);
	//	Leo donde no están los diodos
	if(0==GPIO_Get(PIN_TECLADO_COL0))
		return CODIGO_AST;
	if(0==GPIO_Get(PIN_TECLADO_COL1))
		return CODIGO_0;
	if(0==GPIO_Get(PIN_TECLADO_COL2))
		return CODIGO_NUM;
	if(0==GPIO_Get(PIN_TECLADO_COL3))
		return CODIGO_D;

	return NO_KEY;
}

void TECLADO_Antirebote(void)
{
	codigo_actual = TECLADO_Leer_HW();
	if(codigo_actual == codigo_anterior)
	{
		if(contador >= CANT_TECLA_VALIDA)
			codigo_valido = codigo_actual;
		//TECLADO_PUSH(codigo_actual);
		contador++;
	}else
		contador=0;
	codigo_anterior=codigo_actual;
}

uint8_t TECLADO_Leer(void)
{
	uint8_t Temporal = codigo_valido;
	codigo_valido=NO_KEY;
	return Temporal;
}


void TECLADO_Antirebote_Mantiene_Tecla(void)
{
	codigo_actual = TECLADO_Leer_HW();
	if(codigo_actual == codigo_anterior)
	{
		if(contador >= CANT_TECLA_VALIDA)
			codigo_valido = codigo_actual;
		if(contador == CANT_TECLA_VALIDA_REPETICION)
		{
			//codigo_valido=0x80;
			codigo_valido=codigo_actual;
			//codigo_valido=codigo_actual+0x80;
			contador--;
		}
		contador++;
	}else
		contador=0;
	codigo_anterior=codigo_actual;
}

void TECLADO_PUSH(uint8_t codigo)
{
	Buffer_teclado[IndiceIn]=codigo;
	IndiceIn++;
	IndiceIn%=TAMANIO_BUFFER_TECLADO;
}

uint8_t TECLADO_POP(void)
{
	uint8_t Temporal = NO_KEY;
	if(IndiceOut!=IndiceIn)
	{
		Temporal=Buffer_teclado[IndiceOut];
		IndiceOut++;
		IndiceOut%=TAMANIO_BUFFER_TECLADO;
	}
	return Temporal;
}
