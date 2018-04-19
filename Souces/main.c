#include "derivative.h" /* include peripheral declarations */
#define GLOBLE_VAR  //只需在main.c中定义一次，用来防止全局变量的重复定义
#include "CLK.h"
#include "GPIO.h"
#include "PWT.h"
#include "UART.h"
#include "stdio.h"//hello Git I am WangChao

#ifdef  __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#endif /* __GNUC__ */

// 注册pwt中断向量
void PWT_IRQHandler(void);
//#define isr_pwt  PWT_IRQHandler

//uint16_t count = 10000;

int main()
{
    int i ;
    int MODE = 0;
    timer_counter = 0;
    counter_overflow = 0;
    //timer_counter=0;
    frequency = 0, period = 0;
    decimals = 0; //数据初始化
    Clk_Init();
    PWT_Init();
    //ENABLE_INTERRUPTS;
    //NVIC_EnableIRQ(PWT_IRQn);
    UART_Init();
    GPIO_Init();
    //OUTPUT_SET(PTG, PTG1); //关闭
    //for(i=0;i<1000;i++)
    //for(j=0;j<1000;j++);
    //OUTPUT_CLEAR(PTG, PTG1); //打开
    //for(i=0;i<1000;i++)
    // for(j=0;j<1000;j++);
    //printf("hello");
    while (1)
    {
        if (MODE)
        {
            PWT_R1 ^= PWT_R1_PINSEL(1);//清零PWT输入选择位
            PWT_R1 |= PWT_R1_PINSEL(0);//选择PWTIN0
            if (counter_overflow)

            {
                //counter_overflow = 0;
                OUTPUT_TOGGLE(PTG, PTG0); //红灯闪烁
            }
            else
            {
                Pulse_Measurement();//计算
                printf("############################\r\n");
                printf("LEFT= %d.%d \n", (uint_16)frequency, (uint_16)decimals);//打印频率值
                //counter_overflow = 1;
                positive_pulse = 0;
                negative_pulse = 0;//清零positive_pulse和negative_pulse = 0防止在另一通道打开时继续打印出来
                OUTPUT_TOGGLE(PTG, PTG1);//蓝灯闪烁
                //printf("period=%d",(uint_16)period);
                //printf("d = %lu \n",negative_pulse);
                //printf("P = %lu \n",positive_pulse);

            }
        }
        else
        {
            PWT_R1 ^= PWT_R1_PINSEL(0);//清零PWT输入选择位
            PWT_R1 |= PWT_R1_PINSEL(1);//选择PWTIN1
            if (counter_overflow)

            {
                //counter_overflow = 0;
                OUTPUT_TOGGLE(PTG, PTG0); //红灯闪烁
            }
            else
            {
                Pulse_Measurement();//计算
                printf("############################\r\n");
                printf("RIGHT = %d.%d \n", (uint_16)frequency, (uint_16)decimals);//打印
                //counter_overflow = 1;
                positive_pulse = 0;
                negative_pulse = 0;//清零positive_pulse和negative_pulse = 0防止在另一通道打开时继续打印出来
                OUTPUT_TOGGLE(PTG, PTG1);//蓝灯闪烁
                //printf("period=%d",(uint_16)period);
                //printf("d = %lu \n",negative_pulse);
                //printf("P = %lu \n",positive_pulse);


            }
        }
        //for (i = 65536; i > 0; i--)
        ;
        MODE = ~MODE;//翻转MODE来切换PWT输入通道
    }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */

    Uart_SendChar(ch);
    return ch;
}
