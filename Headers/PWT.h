#ifndef PWT_H
#define PWT_H

#include "derivative.h"

#define PWT_IRQ_NUMBER     29
//防止全局变量重复声明的前缀处理方法
#ifdef GLOBLE_VAR                 //GLOBLE_VAR在main.c文件中宏定义
#define G_VAR_PREFIX          //main.c文件中使用全局变量不加“extern”前缀
#else
#define G_VAR_PREFIX  extern  //其他文件中使用全局变量自动加“extern”前缀
#endif
//声明全局变量（全局变量类型前一律前缀G_VAR_PREFIX）
G_VAR_PREFIX char g_uart_num;
G_VAR_PREFIX uint_32 positive_pulse, negative_pulse;
G_VAR_PREFIX uint_8 counter_overflow;
G_VAR_PREFIX uint_32 timer_counter;
G_VAR_PREFIX float frequency, period;
G_VAR_PREFIX float decimals;
//G_VAR_PREFIX int MODE = 0;

void PWT_Init(void);
void Pulse_Measurement(void);
void Pulse_Measurement(void);

#endif
