#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
#include "misc.h"

// 延时的微秒数
extern __IO uint64_t time_delay_us;

// 初始化SysTick产生时间中断的间隔为1us
void SysTick_Init(void);

// 延时指定微秒数
void delay_us(__IO uint64_t us);

// 延时指定毫秒数
void delay_ms(__IO uint64_t ms);

// 延时指定秒数
void delay_s(__IO uint64_t s);

#endif