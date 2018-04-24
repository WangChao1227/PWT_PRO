# include "PIT.h"

void PIT_Init(uint_8 pitno, uint_32 int_ms)
{
    uint_32 mod_value;
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //使能PIT时钟门
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //使能PIT模块
    NVIC_DisableIRQ(PIT_CH0_IRQ_NO + pitno);   //关接收引脚的IRQ中断
    mod_value = int_ms * BUS_CLK_KHZ;
    PIT_LDVAL(pitno) = mod_value;
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TIE_MASK);     //开pit模块中断
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TEN_MASK);     //使能pit模块运行
    NVIC_EnableIRQ(PIT_CH0_IRQ_NO + pitno);   //开接收引脚的IRQ中断
}
void PIT_isr()
{

}