#ifndef PWT_H
#define PWT_H

#include "derivative.h"

#define PWT_IRQ_NUMBER     29
//��ֹȫ�ֱ����ظ�������ǰ׺������
#ifdef GLOBLE_VAR                 //GLOBLE_VAR��main.c�ļ��к궨��
#define G_VAR_PREFIX          //main.c�ļ���ʹ��ȫ�ֱ������ӡ�extern��ǰ׺
#else
#define G_VAR_PREFIX  extern  //�����ļ���ʹ��ȫ�ֱ����Զ��ӡ�extern��ǰ׺
#endif
//����ȫ�ֱ�����ȫ�ֱ�������ǰһ��ǰ׺G_VAR_PREFIX��
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
