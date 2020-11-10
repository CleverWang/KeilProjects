#ifndef TIMER_H
#define TIMER_H

#include "misc.h"
#include "LED.h"

// 初始化TIM2的NVIC
void TIM2_NVIC_Config(void);

// 初始化TIM2
void TIM2_Config(void);

#endif