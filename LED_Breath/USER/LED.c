#include "LED.h"

void LED_GPIO_Config(void)
{
	// GPIO初始化结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// 使能GPIO所在外设总线的时钟，LED连接针脚为PB11，即GPIOB的11号针脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	
	// LED连接在GPIOB的11号针脚上
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	// GPIO速度，设置为最高
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	// GPIO模式，推挽式输出
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	
	// 根据初始化结构体对GPIOB进行初始化
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}