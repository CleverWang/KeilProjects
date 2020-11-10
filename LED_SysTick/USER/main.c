#include "LED.h"
#include "Timer.h"

void delay(unsigned int count);

int main(void)
{
	SystemInit(); // ��ʼ��ϵͳ��ʹϵͳʱ��Ϊ72MHz
	SysTick_Init();
	LED_GPIO_Config();
	
	// 1s��˸һ��
	while (1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_11);
		delay_ms(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_11);
		delay_ms(500);
	}
	
	return 0;
}