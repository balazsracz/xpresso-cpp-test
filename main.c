/*
===============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC11xx.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

#include "src/ProgramLoop.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP ;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

	// TODO: insert code here
	/* Enable AHB clock to the GPIO domain. */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

	LPC_GPIO0->DIR |= (1<<7);

	RunProgramLoop();

	// Enter an infinite loop, just incrementing a counter
	volatile static int i = 0 ;
	while(1) {
		const int bit = 16;
		const int mask = (1<<bit)-1;
		if (!(i & mask)) {
			if ((i >> bit) & 1) {
				LPC_GPIO0->DATA |= (1<<7);
			} else {
				LPC_GPIO0->DATA &= ~(1<<7);
			}
		}
		i++ ;
	}
	return 0 ;
}
