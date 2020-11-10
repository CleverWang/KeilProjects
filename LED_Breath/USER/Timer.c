#include "Timer.h"

uint8_t PWM_HIGH_PERCENT = 0; // 占空比,100内占的个数
uint8_t LED_STATUS = 0; // 记录当前LED在100内的个数
uint8_t HIGH_STEP = 0; // 变化的占空比
uint32_t BREATH_INTERVAL = 0; // 每个占空比持续的时长计数，决定了占空比切换频率，计算：占空比切换频率=灯亮灭频率/BREATH_INTERVAL最高值
uint8_t IS_HIGH = 0x00; // 占空比是否达到最高

// 设置占空比
void Set_PWM_High_Percent(uint8_t high_percent)
{
	PWM_HIGH_PERCENT = high_percent;
}

// TIM2的中断处理函数
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // 判断中断是否发生
	{
		++LED_STATUS;
		// 时钟频率为200KHz，灯亮灭频率为2KHz
		// 500us内，5*PWM_HIGH_PERCENT的时间处于亮灯状态
		if (LED_STATUS <= PWM_HIGH_PERCENT)
		{
			LED_ON;
		}
		// 其余时间处于熄灭状态
		else if (LED_STATUS <= 100)
		{
			LED_OFF;
		}
		// 占空比切换频率为25HZ
		else
		{
			LED_STATUS = 0;
			++BREATH_INTERVAL;
		}
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); // 清除TIM的待处理中断标志位
	}
}

// 隔一定时间将占空比由小到大再由大到小
void Breath(void)
{
	// 2KHz / 80 = 25Hz
	if(BREATH_INTERVAL >= 80)
	{
		if(IS_HIGH == 0x00)
		{
			if(HIGH_STEP <= 99)
			{
				HIGH_STEP += 4;
			}
      else
      {
        IS_HIGH = 0xff;
      }
    }
    else if(IS_HIGH == 0xff)
    {
			if(HIGH_STEP > 0)
			{
				HIGH_STEP -= 4;
			}
			else
			{
				IS_HIGH = 0x00;
      }
    }
    Set_PWM_High_Percent(HIGH_STEP);
    BREATH_INTERVAL = 0;
  }
}

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
	TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1; // 预分频，将频率/TIM_Prescaler得到TIM的频率，此处TIM频率为2MHz
	TIM_TimeBaseStructure.TIM_Period = 10 - 1; // 在TIM频率下，每次计数的长度，此处计数周期为5us，即5us产生一次中断
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // 清除TIM的待处理中断位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // 使能TIM的更新中断（溢出中断，计数满以后）
	TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}