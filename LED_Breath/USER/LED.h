#ifndef LED_H
#define LED_H

#include "stm32f10x.h"

#define LED_ON GPIO_ResetBits(GPIOB, GPIO_Pin_11) // LED��
#define LED_OFF GPIO_SetBits(GPIOB, GPIO_Pin_11) // LED��

// ����LED��ӦGPIO�˿�
void LED_GPIO_Config(void);

#endif