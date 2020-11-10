#include "Timer.h"

__IO uint64_t time_delay_us;

void SysTick_Init(void)
{
	// ����SysTick����ֵ������SystemInit()֮��ϵͳʱ��Ϊ72MHZ
	// Ϊ������ÿ1us����һ��ʱ���жϣ�����ֵ����Ϊ��1us / (1 / 72Mhz) = 72��
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

// SysTickʱ���жϴ�����
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