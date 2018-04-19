
#include "PWT.h"
#define isr_pwt  PWT_IRQHandler

const float pwt_clock = 156250.0;

void PWT_Init()
{
    SIM_SCGC |=  SIM_SCGC_PWT_MASK;        //��PWT��ʱ��
    PWT_R1 |= PWT_R1_PRE(7);               //PWTʱ��ԴԤ��Ƶѡ��128
    PWT_R1 |= PWT_R1_EDGE(0);              //�ӵ�һ���½��ؿ�ʼ����
    //PWT_R1 |= PWT_R1_PINSEL(0);            //ʹ��PWTIN0
    SIM_PINSEL1 |= SIM_PINSEL1_PWTIN0PS_SHIFT;//ѡ��PWTIN0������PTD5��
    //PWT_R1 |= PWT_R1_PINSEL(1);            //ʹ��PWTIN1
    SIM_PINSEL1 |= SIM_PINSEL1_PWTIN1PS_MASK;//ѡ��PWTIN1������PTH7��

    PWT_R1 |= PWT_R1_POVIE_MASK;           //ʹ������ж�
    PWT_R1 |= PWT_R1_PRDYIE_MASK;          //ʹ�����ݾ����ж�
    PWT_R1 |= PWT_R1_PWTIE_MASK;           //ʹ��PWTģ���ж�
    PWT_R1 |= PWT_R1_PWTEN_MASK;           //ʹ��PWTģ��

    NVIC_EnableIRQ(PWT_IRQ_NUMBER);        //��PWT�ж�
}
//=========================================================================
//�������ƣ�Pulse_Measurement
//���ܸ�Ҫ���������
//����˵������
//�������أ���
//=========================================================================
void Pulse_Measurement(void)
{
    frequency = (pwt_clock) / (positive_pulse + negative_pulse); //�����ź�Ƶ��
    period = 1.0 / frequency;                  //�����ź�����
    period = period * 1000;                    //��ת���ɺ���

    decimals = frequency - (uint_8)frequency;
    decimals = decimals * 10;
}
void isr_pwt()
{
    if ((PWT_R1 & PWT_R1_PWTOV_MASK))   // If overflow interrupt has occurred
    {
        PWT_R1 ^= PWT_R1_PWTOV_MASK;  // Clear overflow flag
        positive_pulse = 0;
        negative_pulse = 0;
        counter_overflow = 1;
    }

    if ((PWT_R1 & PWT_R1_PWTRDY_MASK))  // If data ready interrupt has occurred
    {
        (void)PWT_R1;                                 // Read PWT Register 1
        counter_overflow = 0;
        PWT_R1 ^= PWT_R1_PWTRDY_MASK;                 //Clear data ready flag
        positive_pulse = (PWT_R1 >> 16 & 0x0000FFFF) ; // Read positive measurement
        negative_pulse = PWT_R2 & 0x0000FFFF;         // Read negative measurement
        (void)PWT_R1;                                 // Read PWT Register 1
        PWT_R1 ^= PWT_R1_PWTRDY_MASK;                 //Clear data ready flag
        //Pulse_Measurement();
    }
}
