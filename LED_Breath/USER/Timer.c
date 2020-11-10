#include "Timer.h"

uint8_t PWM_HIGH_PERCENT = 0; // ռ�ձ�,100��ռ�ĸ���
uint8_t LED_STATUS = 0; // ��¼��ǰLED��100�ڵĸ���
uint8_t HIGH_STEP = 0; // �仯��ռ�ձ�
uint32_t BREATH_INTERVAL = 0; // ÿ��ռ�ձȳ�����ʱ��������������ռ�ձ��л�Ƶ�ʣ����㣺ռ�ձ��л�Ƶ��=������Ƶ��/BREATH_INTERVAL���ֵ
uint8_t IS_HIGH = 0x00; // ռ�ձ��Ƿ�ﵽ���

// ����ռ�ձ�
void Set_PWM_High_Percent(uint8_t high_percent)
{
	PWM_HIGH_PERCENT = high_percent;
}

// TIM2���жϴ�����
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) // �ж��ж��Ƿ���
	{
		++LED_STATUS;
		// ʱ��Ƶ��Ϊ200KHz��������Ƶ��Ϊ2KHz
		// 500us�ڣ�5*PWM_HIGH_PERCENT��ʱ�䴦������״̬
		if (LED_STATUS <= PWM_HIGH_PERCENT)
		{
			LED_ON;
		}
		// ����ʱ�䴦��Ϩ��״̬
		else if (LED_STATUS <= 100)
		{
			LED_OFF;
		}
		// ռ�ձ��л�Ƶ��Ϊ25HZ
		else
		{
			LED_STATUS = 0;
			++BREATH_INTERVAL;
		}
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update); // ���TIM�Ĵ������жϱ�־λ
	}
}

// ��һ��ʱ�佫ռ�ձ���С�������ɴ�С
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
	TIM_TimeBaseStructure.TIM_Prescaler = 36 - 1; // Ԥ��Ƶ����Ƶ��/TIM_Prescaler�õ�TIM��Ƶ�ʣ��˴�TIMƵ��Ϊ2MHz
	TIM_TimeBaseStructure.TIM_Period = 10 - 1; // ��TIMƵ���£�ÿ�μ����ĳ��ȣ��˴���������Ϊ5us����5us����һ���ж�
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // ���TIM�Ĵ������ж�λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // ʹ��TIM�ĸ����жϣ�����жϣ��������Ժ�
	TIM_Cmd(TIM2, ENABLE); // ʹ��TIM2
}