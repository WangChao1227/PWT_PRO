# include "PIT.h"
#include "derivative.h"

#define PIT_CH0_IRQ_NO 22
#define PIT_CH1_IRQ_NO 23

void PIT_Init(uint_8 pitno, uint_32 int_ms)
{
    uint_32 mod_value;
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //ʹ��PITʱ����
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //ʹ��PITģ��
    NVIC_DisableIRQ(PIT_CH0_IRQ_NO + pitno);   //�ؽ������ŵ�IRQ�ж�
    mod_value = (int_ms * 10000000) / 50 - 1; //����ʱ�ӵ�Ƶ��20MHZ����50ns   ��LDVAL ������ = (���� / ʱ������) -1
    PIT_LDVAL(pitno) = mod_value;             //���ü�������ֵ
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TIE_MASK);     //��pitģ���ж�
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TEN_MASK);     //ʹ��pitģ������
    NVIC_EnableIRQ(PIT_CH0_IRQ_NO + pitno);   //���������ŵ�IRQ�ж�
}
//void PIT_isr()
//{

//}
