/*
 * Note: This file is recreated by the project wizard whenever the MCU is
 *       changed and should not be edited by hand
 */

/* Include the derivative-specific header file */
#include <SKEAZ1284.h>
#include "typedefs.h"

#define  SYSTEM_CLK_KHZ   (DEFAULT_SYSTEM_CLOCK/1000)// 芯片系统时钟频率(KHz)
#define  CORE_CLK_KHZ     SYSTEM_CLK_KHZ           // 芯片内核时钟频率(KHz)
#define  BUS_CLK_KHZ      (SYSTEM_CLK_KHZ/2)         // 芯片总线时钟频率(KHz)

// 2．定义开关总中断
#define ENABLE_INTERRUPTS   __enable_irq   // 开总中断
#define DISABLE_INTERRUPTS  __disable_irq  // 关总中断

// 3．位操作宏函数（置位、清位、获得寄存器一位的状态）
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    // 置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  // 清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  // 获得寄存器一位的状态

// 4．重定义基本数据类型（类型别名宏定义）
typedef unsigned char uint_8;   // 无符号8位数，字节
typedef unsigned short int uint_16;  // 无符号16位数，字
typedef unsigned long int uint_32;  // 无符号32位数，长字
typedef char int_8;    // 有符号8位数
typedef short int int_16;   // 有符号16位数
typedef int int_32;   // 有符号32位数
// 不优化类型
typedef volatile uint_8 vuint_8;  // 不优化无符号8位数，字节
typedef volatile uint_16 vuint_16; // 不优化无符号16位数，字
typedef volatile uint_32 vuint_32; // 不优化无符号32位数，长字
typedef volatile int_8 vint_8;   // 不优化有符号8位数
typedef volatile int_16 vint_16;  // 不优化有符号16位数
typedef volatile int_32 vint_32;  // 不优化有符号32位数
