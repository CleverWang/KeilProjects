#include "Timer.h"

__IO uint64_t time_delay_us;

void SysTick_Init(void)
{
	// 设置SysTick重载值，经过SystemInit()之后，系统时钟为72MHZ
	// 为了设置每1us产生一个时钟中断，重载值设置为（1us / (1 / 72Mhz) = 72）
	// while (SysTick_Config(72) == 1)
	while (SysTick_Config(SystemCoreClock / 1000000) == 1)
	{
		;
	}
}

void time_delay_us_dec(void)
{
	if (time_delay_us != 0)
	{
		--time_delay_us;
	}
}

// SysTick时钟中断处理函数
void SysTick_Handler(void)
{
	time_delay_us_dec();
}

void delay_us(__IO uint64_t us)
{
	time_delay_us = us;
	while (time_delay_us)
	{
		;
	}
}

void delay_ms(__IO uint64_t ms)
{
	delay_us(ms * 1000);
}

void delay_s(__IO uint64_t s)
{
	delay_ms(s * 1000);
}