#include "Timer.h"

int main(void)
{
	SystemInit(); // ��ʼ��ϵͳ��ʹϵͳʱ��Ϊ72MHz
	LED_GPIO_Config();
	LED_OFF; // ��ʼ״̬LED����
	TIM2_NVIC_Config();
	TIM2_Config();
	
	while(1)
	{
		Breath();
	}
	
	return 0;
}