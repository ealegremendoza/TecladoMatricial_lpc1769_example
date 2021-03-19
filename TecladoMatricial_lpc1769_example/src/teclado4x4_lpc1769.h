/*
 * Teclado4x4_lpc1769.h
 *
 *  Created on: 19 mar. 2021
 *      Author: ealegremendoza
 */

#ifndef TECLADO4X4_LPC1769_H_
#define TECLADO4X4_LPC1769_H_
#include "headers.h"

#define PIN_TECLADO_FIL0		2,1
#define PIN_TECLADO_FIL1		2,2
#define PIN_TECLADO_FIL2		2,3
#define PIN_TECLADO_FIL3		2,4
#define PIN_TECLADO_COL0		2,6
#define PIN_TECLADO_COL1		2,8
#define PIN_TECLADO_COL2		2,10
#define PIN_TECLADO_COL3		2,11
#define TECLADO_PIN_FUNC 		FUNC_GPIO
#define TECLADO_FIL_PIN_DIR		DIR_SALIDA
#define TECLADO_COL_PIN_DIR		DIR_ENTRADA
#define TECLADO_FIL_PIN_MODE	MODE_NONE
#define TECLADO_COL_PIN_MODE	MODE_PULLUP

/* CODIGOS DE TECLA	*/
#define CODIGO_0	'0'
#define CODIGO_1	'1'
#define CODIGO_2	'2'
#define CODIGO_3	'3'
#define CODIGO_4	'4'
#define CODIGO_5	'5'
#define CODIGO_6	'6'
#define CODIGO_7	'7'
#define CODIGO_8	'8'
#define CODIGO_9	'9'
#define	CODIGO_A	'A'
#define	CODIGO_B	'B'
#define	CODIGO_C	'C'
#define	CODIGO_D	'D'
#define	CODIGO_NUM	'#'
#define CODIGO_AST	'*'
#define NO_KEY		0xFF

#define CANT_TECLA_VALIDA				1
#define CANT_TECLA_VALIDA_REPETICION 	5

/*	fifo para teclado	*/
#define TAMANIO_BUFFER_TECLADO	50


void TECLADO_Init(void);
uint8_t TECLADO_Leer_HW(void);
void TECLADO_Antirebote(void);
void TECLADO_Antirebote_Mantiene_Tecla(void);
uint8_t TECLADO_Leer(void);
void TECLADO_PUSH(uint8_t codigo);
uint8_t TECLADO_POP(void);
#endif /* TECLADO4X4_LPC1769_H_ */
