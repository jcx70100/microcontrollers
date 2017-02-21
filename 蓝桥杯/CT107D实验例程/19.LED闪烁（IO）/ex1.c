/*******************************************************************************  
* 文件名称：LED闪烁实验 (IO方式) 
//此种方法能够熟悉开发板上面各个芯片的使用方法
* 实验目的：1.掌握单片机IO口操作的基本方法
*           2.掌握软件延时函数的设计方法
       
* 程序说明：LED以0.2S为间隔亮灭(STC89C52RC单片机)  J13选择为IO方式
* 日期版本：NUAA  2015-8
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "intrins.h"

sbit  HC138A = P2^5;
sbit  HC138B = P2^6;
sbit  HC138C = P2^7;

//延时函数 软件延时
void delay(int ms) //10ms一次
{
    unsigned char i,j;
    for(i=0; i<220; i++)
    {
        for(j=0; j<ms; j++)
        {
            ;
        }
    } 
}
void U6suocun(void) //LED对应锁存器U6控制端LE 从高位变为低位
{
   HC138A = 0;
   HC138B = 0;
   HC138C = 1; //Y4 为0  其他为高
   _nop_();
   _nop_();
   HC138A = 0;
   HC138B = 0;
   HC138C = 0; //Y4 为1  （此时只有Y0是0 不过Y0在板子上没有用到）
  
}

//主函数
void main(void)
{
     HC138A = 0;
     HC138B = 0;
     HC138C = 0; //初始化 
	while(1)
    {
		P0 = 0xff;
		U6suocun();
		delay(120);
		P0 = 0x00;
		U6suocun();
		delay(120);
    }
}