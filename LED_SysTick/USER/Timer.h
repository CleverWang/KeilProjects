#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"
#include "misc.h"

// ��ʱ��΢����
extern __IO uint64_t time_delay_us;

// ��ʼ��SysTick����ʱ���жϵļ��Ϊ1us
void SysTick_Init(void);

// ��ʱָ��΢����
void delay_us(__IO uint64_t us);

// ��ʱָ��������
void delay_ms(__IO uint64_t ms);

// ��ʱָ������
void delay_s(__IO uint64_t s);

#endif