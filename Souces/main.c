#include "derivative.h" /* include peripheral declarations */
#define GLOBLE_VAR  //ֻ����main.c�ж���һ�Σ�������ֹȫ�ֱ������ظ�����
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

// ע��pwt�ж�����
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
    decimals = 0; //���ݳ�ʼ��
    Clk_Init();
    PWT_Init();
    //ENABLE_INTERRUPTS;
    //NVIC_EnableIRQ(PWT_IRQn);
    UART_Init();
    GPIO_Init();
    //OUTPUT_SET(PTG, PTG1); //�ر�
    //for(i=0;i<1000;i++)
    //for(j=0;j<1000;j++);
    //OUTPUT_CLEAR(PTG, PTG1); //��
    //for(i=0;i<1000;i++)
    // for(j=0;j<1000;j++);
    //printf("hello");
    while (1)
    {
        if (MODE)
        {
            PWT_R1 ^= PWT_R1_PINSEL(1);//����PWT����ѡ��λ
            PWT_R1 |= PWT_R1_PINSEL(0);//ѡ��PWTIN0
            if (counter_overflow)

            {
                //counter_overflow = 0;
                OUTPUT_TOGGLE(PTG, PTG0); //�����˸
            }
            else
            {
                Pulse_Measurement();//����
                printf("############################\r\n");
                printf("LEFT= %d.%d \n", (uint_16)frequency, (uint_16)decimals);//��ӡƵ��ֵ
                //counter_overflow = 1;
                positive_pulse = 0;
                negative_pulse = 0;//����positive_pulse��negative_pulse = 0��ֹ����һͨ����ʱ������ӡ����
                OUTPUT_TOGGLE(PTG, PTG1);//������˸
                //printf("period=%d",(uint_16)period);
                //printf("d = %lu \n",negative_pulse);
                //printf("P = %lu \n",positive_pulse);

            }
        }
        else
        {
            PWT_R1 ^= PWT_R1_PINSEL(0);//����PWT����ѡ��λ
            PWT_R1 |= PWT_R1_PINSEL(1);//ѡ��PWTIN1
            if (counter_overflow)

            {
                //counter_overflow = 0;
                OUTPUT_TOGGLE(PTG, PTG0); //�����˸
            }
            else
            {
                Pulse_Measurement();//����
                printf("############################\r\n");
                printf("RIGHT = %d.%d \n", (uint_16)frequency, (uint_16)decimals);//��ӡ
                //counter_overflow = 1;
                positive_pulse = 0;
                negative_pulse = 0;//����positive_pulse��negative_pulse = 0��ֹ����һͨ����ʱ������ӡ����
                OUTPUT_TOGGLE(PTG, PTG1);//������˸
                //printf("period=%d",(uint_16)period);
                //printf("d = %lu \n",negative_pulse);
                //printf("P = %lu \n",positive_pulse);


            }
        }
        //for (i = 65536; i > 0; i--)
        ;
        MODE = ~MODE;//��תMODE���л�PWT����ͨ��
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
