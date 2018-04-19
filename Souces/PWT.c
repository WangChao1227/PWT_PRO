
#include "PWT.h"
#define isr_pwt  PWT_IRQHandler

const float pwt_clock = 156250.0;

void PWT_Init()
{
    SIM_SCGC |=  SIM_SCGC_PWT_MASK;        //打开PWT的时钟
    PWT_R1 |= PWT_R1_PRE(7);               //PWT时钟源预分频选择128
    PWT_R1 |= PWT_R1_EDGE(0);              //从第一个下降沿开始测量
    //PWT_R1 |= PWT_R1_PINSEL(0);            //使能PWTIN0
    SIM_PINSEL1 |= SIM_PINSEL1_PWTIN0PS_SHIFT;//选择PWTIN0引脚在PTD5上
    //PWT_R1 |= PWT_R1_PINSEL(1);            //使能PWTIN1
    SIM_PINSEL1 |= SIM_PINSEL1_PWTIN1PS_MASK;//选择PWTIN1引脚在PTH7上

    PWT_R1 |= PWT_R1_POVIE_MASK;           //使能溢出中断
    PWT_R1 |= PWT_R1_PRDYIE_MASK;          //使能数据就绪中断
    PWT_R1 |= PWT_R1_PWTIE_MASK;           //使能PWT模块中断
    PWT_R1 |= PWT_R1_PWTEN_MASK;           //使能PWT模块

    NVIC_EnableIRQ(PWT_IRQ_NUMBER);        //打开PWT中断
}
//=========================================================================
//函数名称：Pulse_Measurement
//功能概要：脉冲测量
//参数说明：无
//函数返回：无
//=========================================================================
void Pulse_Measurement(void)
{
    frequency = (pwt_clock) / (positive_pulse + negative_pulse); //计算信号频临
    period = 1.0 / frequency;                  //计算信号周期
    period = period * 1000;                    //秒转化成毫秒

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
