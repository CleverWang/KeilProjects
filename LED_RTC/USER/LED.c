#include "LED.h"

void LED_GPIO_Config(void)
{
	// GPIO��ʼ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// ʹ��GPIO�����������ߵ�ʱ�ӣ�LED�������ΪPB11����GPIOB��11�����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	// LED������GPIOB��11�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	// GPIO�ٶȣ�����Ϊ���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	// GPIOģʽ������ʽ���
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	// ���ݳ�ʼ���ṹ���GPIOB���г�ʼ��
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}