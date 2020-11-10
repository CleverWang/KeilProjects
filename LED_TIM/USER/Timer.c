#include "Timer.h"

void TIM2_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// NVIC优先级组0，0 bit for PreemptionPriority and 4 bits for SubPriority
	// PreemptionPriority抢占优先级，决定了是否可以抢占比它抢占优先级低的中断
	// SubPriority子优先级，在抢占优先级相同的情况下，决定了是否可以抢占比它从优先级低的中断
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // 中断通道为TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开启对应外设总线时钟
	TIM_DeInit(TIM2); // 恢复默认
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1; // 预分频，将频率/TIM_Prescaler得到TIM的频率，此处TIM频率为2000Hz
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1; // 在TIM频率下，每次计数的长度，此处计数周期为500ms，即500ms产生一次中断
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除TIM的待处理中断位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM的更新中断（溢出中断，计数满以后）
	TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}

// TIM2的中断处理函数
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // 判断中断是否发生
	{
		uint8_t led_status = GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11); // 读取LED的GPIO当前的状态
		GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)1 - led_status); // 反转当前状态
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); // 清除TIM的待处理中断标志位
	}
}