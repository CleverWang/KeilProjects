#include "Timer.h"

void RTC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn; // RTC�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_Config(void)
{
	// ����BKP��PWRģ���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	// ʹ�ܵ�Դ���ƼĴ�����DBPλ������Ա��ݼĴ�����RTC�ķ���
	PWR_BackupAccessCmd(ENABLE);
	// Ĭ�ϳ�ʼ�����ݼĴ���
	BKP_DeInit();
	// ʹ��LSE���ⲿʱ��Դ
	RCC_LSEConfig(RCC_LSE_ON);
	// �ȴ��ⲿʱ��Դ����
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
		;
	}
	// ʹ��LSE��ΪRTCʱ��
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	// ʹ��RTC
	RCC_RTCCLKCmd(ENABLE);
	// �ȴ�RTC��APB1ʱ��ͬ��
	RTC_WaitForSynchro();
	// �ȴ�RTC�Ĵ���д�������
	RTC_WaitForLastTask();
	// ����RTC�жϣ����ж�
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	// ����RTCԤ��Ƶ���ⲿʱ��ԴƵ��Ϊ32.768KHz����RTCƵ��Ϊ32.768KHz/(16383+1)=2Hz
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