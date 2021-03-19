/*
===============================================================================
 Name        : main.c
 Author      : ealegremendoza
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "headers.h"

void SystemInit(void)
{
	InitPLL();
	SysTick_Init(1000);
	TECLADO_Init();
}

void DoSomething (void)
{
	uint8_t temporal = TECLADO_POP();
	if(temporal!=NO_KEY)
	{
		printf("%c\n",temporal);
	}
}

int main(void) {
	SystemInit();
	DEBUGOUT("> main.\n");
    while(1) {
    	TECLADO_PUSH(TECLADO_Leer());
    	DoSomething();
    }
    return 0 ;
}
