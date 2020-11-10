#include "Timer.h"

int main(void)
{
	SystemInit(); // 初始化系统，使系统时钟为72MHz
	LED_GPIO_Config();
	LED_OFF; // 初始状态LED灯灭
	RTC_NVIC_Config();
	RTC_Config();
	
	while(1)
	{
		;
	}
	
	return 0;
}