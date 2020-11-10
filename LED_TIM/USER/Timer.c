#include "Timer.h"

void TIM2_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// NVIC���ȼ���0��0 bit for PreemptionPriority and 4 bits for SubPriority
	// PreemptionPriority��ռ���ȼ����������Ƿ������ռ������ռ���ȼ��͵��ж�
	// SubPriority�����ȼ�������ռ���ȼ���ͬ������£��������Ƿ������ռ���������ȼ��͵��ж�
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // �ж�ͨ��ΪTIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // ������Ӧ��������ʱ��
	TIM_DeInit(TIM2); // �ָ�Ĭ��
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1; // Ԥ��Ƶ����Ƶ��/TIM_Prescaler�õ�TIM��Ƶ�ʣ��˴�TIMƵ��Ϊ2000Hz
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // ��TIMƵ���£�ÿ�μ����ĳ��ȣ��˴���������Ϊ500ms����500ms����һ���ж�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // ���TIM�Ĵ������ж�λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ʹ��TIM�ĸ����жϣ�����жϣ��������Ժ�
	TIM_Cmd(TIM2, ENABLE); // ʹ��TIM2
}

// TIM2���жϴ�����
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // �ж��ж��Ƿ���
	{
		uint8_t led_status = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11); // ��ȡLED��GPIO��ǰ��״̬
		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)1 - led_status); // ��ת��ǰ״̬
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); // ���TIM�Ĵ������жϱ�־λ
	}
}