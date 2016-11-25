/*
 * main.cpp
 *
 *  Created on: 25 lis 2016
 *      Author: Adam Tomaja
 */
#include <stddef.h>

#include "stm32l1xx.h"
#include "usart/usart.h"
#include "main.h"

int main(void) {
	init_clocks();
	init_usart();
	init_gpio();

	print("Hello World from STM32!");
	for (;;);
}

void init_clocks() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

void init_usart() {
	USART_InitTypeDef uart;
	USART_StructInit(&uart);
	USART_Init(USART3, &uart);
	uart.USART_BaudRate = 9600;
	USART_Cmd(USART3, ENABLE);
}

void init_gpio() {
	// TX pin
	GPIO_InitTypeDef txOutput;
	GPIO_StructInit(&txOutput);
	txOutput.GPIO_Pin = GPIO_Pin_10;
	txOutput.GPIO_PuPd = GPIO_PuPd_UP;
	txOutput.GPIO_Mode = GPIO_Mode_AF;
	txOutput.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &txOutput);

	// RX pin
	GPIO_InitTypeDef rxInput;
	GPIO_StructInit(&rxInput);
	rxInput.GPIO_Pin = GPIO_Pin_11;
	rxInput.GPIO_PuPd = GPIO_PuPd_NOPULL;
	rxInput.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &rxInput);

	// Configure alternative functions for pins
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
}

extern "C" {

#ifdef  USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/*
 * Minimal __assert_func used by the assert() macro
 * */
void __assert_func(const char *file, int line, const char *func,
		const char *failedexpr) {
	while (1) {
	}
}

/*
 * Minimal __assert() uses __assert__func()
 * */
void __assert(const char *file, int line, const char *failedexpr) {
	__assert_func(file, line, NULL, failedexpr);
}

}
