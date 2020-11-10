#include "LED.h"
#include "Timer.h"

void delay(unsigned int count);

int main(void)
{
	SystemInit(); // 初始化系统，使系统时钟为72MHz
	SysTick_Init();
	LED_GPIO_Config();
	
	// 1s闪烁一次
	while (1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		delay_ms(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		delay_ms(500);
	}
	
	return 0;
}