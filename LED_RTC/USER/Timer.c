#include "Timer.h"

void RTC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn; // RTC中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_Config(void)
{
	// 开启BKP和PWR模块的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	// 使能电源控制寄存器的DBP位来允许对备份寄存器和RTC的访问
	PWR_BackupAccessCmd(ENABLE);
	// 默认初始化备份寄存器
	BKP_DeInit();
	// 使能LSE，外部时钟源
	RCC_LSEConfig(RCC_LSE_ON);
	// 等待外部时钟源起振
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
		;
	}
	// 使用LSE作为RTC时钟
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	// 使能RTC
	RCC_RTCCLKCmd(ENABLE);
	// 等待RTC与APB1时钟同步
	RTC_WaitForSynchro();
	// 等待RTC寄存器写操作完成
	RTC_WaitForLastTask();
	// 配置RTC中断，秒中断
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	// 设置RTC预分频，外部时钟源频率为32.768KHz，则RTC频率为32.768KHz/(16383+1)=2Hz
	RTC_SetPrescaler(16383);
	RTC_WaitForLastTask();
}

void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		u8 led_status = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11);
		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)1 - led_status);
		RTC_ClearITPendingBit(RTC_IT_SEC);
		RTC_WaitForLastTask();
	}
}