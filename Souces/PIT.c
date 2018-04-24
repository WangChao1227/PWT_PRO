# include "PIT.h"

void PIT_Init(uint_8 pitno, uint_32 int_ms)
{
    uint_32 mod_value;
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //ʹ��PITʱ����
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //ʹ��PITģ��
    NVIC_DisableIRQ(PIT_CH0_IRQ_NO + pitno);   //�ؽ������ŵ�IRQ�ж�
    mod_value = int_ms * BUS_CLK_KHZ;
    PIT_LDVAL(pitno) = mod_value;
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TIE_MASK);     //��pitģ���ж�
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TEN_MASK);     //ʹ��pitģ������
    NVIC_EnableIRQ(PIT_CH0_IRQ_NO + pitno);   //���������ŵ�IRQ�ж�
}
void PIT_isr()
{

}