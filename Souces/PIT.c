# include "PIT.h"
#include "derivative.h"

#define PIT_CH0_IRQ_NO 22
#define PIT_CH1_IRQ_NO 23

void PIT_Init(uint_8 pitno, uint_32 int_ms)
{
    uint_32 mod_value;
    SIM_SCGC |= SIM_SCGC_PIT_MASK;  //使能PIT时钟门
    PIT_MCR &= ~PIT_MCR_MDIS_MASK;  //使能PIT模块
    NVIC_DisableIRQ(PIT_CH0_IRQ_NO + pitno);   //关接收引脚的IRQ中断
    mod_value = (int_ms * 10000000) / 50 - 1; //总线时钟的频率20MHZ周期50ns   有LDVAL 触发器 = (周期 / 时钟周期) -1
    PIT_LDVAL(pitno) = mod_value;             //配置计数器的值
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TIE_MASK);     //开pit模块中断
    PIT_TCTRL(pitno) |= (PIT_TCTRL_TEN_MASK);     //使能pit模块运行
    NVIC_EnableIRQ(PIT_CH0_IRQ_NO + pitno);   //开接收引脚的IRQ中断
}
//void PIT_isr()
//{

//}
