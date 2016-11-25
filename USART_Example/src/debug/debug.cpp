/*
 * debug.cpp
 *
 *  Created on: 25 lis 2016
 *      Author: Adam Tomaja
 */
#include "stm32l1xx.h"

void debug_println(const char * text) {
	int i = 0;
	while (text[i] != 0) {
		ITM_SendChar(text[i++]);
	}

	ITM_SendChar('\r');
	ITM_SendChar('\n');
}



