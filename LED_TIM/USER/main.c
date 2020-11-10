#include "Timer.h"

int main(void)
{
	SystemInit(); // 初始化系统，使系统时钟为72MHz
	LED_GPIO_Config();
	LED_OFF; // 初始状态LED灯灭
	TIM2_NVIC_Config();
	TIM2_Config();
	
	while(1)
	{
		;
	}
	
	return 0;
}