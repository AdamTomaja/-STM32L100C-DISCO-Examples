#include <stddef.h>
#include "main.h"
#include "stm32l1xx.h"

static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime) {
	TimingDelay = nTime;

	while (TimingDelay != 0)
		;
}

void TimingDelay_Decrement(void) {
	if (TimingDelay != 0x00) {
		TimingDelay--;
	}
}

void send_char(char c) {
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USART3, c);
}

void print(const char * string) {
	while (*string) {
		send_char(*(string++));
	}
}

int usart_receive() {
	if (USART_GetFlagStatus(USART3, USART_FLAG_RXNE)) {
		return USART_ReceiveData(USART3);
	}

	return -1;
}

void debug_println(const char * text) {
	int i = 0;
	while (text[i] != 0) {
		ITM_SendChar(text[i++]);
	}

	ITM_SendChar('\r');
	ITM_SendChar('\n');
}

int main(void) {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART_InitTypeDef uart;

	USART_StructInit(&uart);
	USART_Init(USART3, &uart);
	uart.USART_BaudRate = 9600;
	USART_Cmd(USART3, ENABLE);

	GPIO_InitTypeDef txOutput;
	GPIO_StructInit(&txOutput);
	txOutput.GPIO_Pin = GPIO_Pin_10;
	txOutput.GPIO_PuPd = GPIO_PuPd_UP;
	txOutput.GPIO_Mode = GPIO_Mode_AF;
	txOutput.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOC, &txOutput);

	GPIO_InitTypeDef rxInput;
	GPIO_StructInit(&rxInput);
	rxInput.GPIO_Pin = GPIO_Pin_11;
	rxInput.GPIO_PuPd = GPIO_PuPd_NOPULL;
	rxInput.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &rxInput);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	print("Hello STM32!");

	debug_println("Hello STM32!");

	for (;;)
		;
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
