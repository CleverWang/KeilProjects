#ifndef TIMER_H
#define TIMER_H

#include "misc.h"
#include "LED.h"

// 初始化RTC的NVIC
void RTC_NVIC_Config(void);

// 初始化RTC
void RTC_Config(void);

#endif