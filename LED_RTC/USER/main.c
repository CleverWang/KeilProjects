#include "Timer.h"

int main(void)
{
	SystemInit(); // ��ʼ��ϵͳ��ʹϵͳʱ��Ϊ72MHz
	LED_GPIO_Config();
	LED_OFF; // ��ʼ״̬LED����
	RTC_NVIC_Config();
	RTC_Config();
	
	while(1)
	{
		;
	}
	
	return 0;
}