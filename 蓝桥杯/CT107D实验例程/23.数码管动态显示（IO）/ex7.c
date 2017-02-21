/*******************************************************************************  
* 文件名称：数码管控制实验
* 实验目的：1.掌握数码管动态扫描的基本原理,掌握数码管消除“鬼影”的方法
*           2.掌握51单片机定时器工作模式和配置方法
*           3.掌握keil uvision集成开发环境下，中断服务函数设计方法
* 程序说明：无
* 日期版本：2015-8 NUAA  
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "intrins.h"

sbit  HC138A = P2^5;
sbit  HC138B = P2^6;
sbit  HC138C = P2^7;               

//以下是P25 P26 P27变化对应使Y0-Y7为0
#define  Y0   0x1f 
#define  Y1   0x3f     
#define  Y2   0x5f  
#define  Y3   0x7f 
#define  Y4   0x9f 
#define  Y5   0xbf 
#define  Y6   0xdf   
#define  Y7   0xff   

                                //0    1    2    3    4    5    6    7    8    9  关闭
code unsigned char duan[11] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xff};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};

unsigned char i = 0;
void display(void);
void U7suocun(void);
void U8suocun(void);


//段锁存器锁存
void U7suocun(void) //LED对应锁存器U7控制端LE 从高位变为低位
{
     //Y7 为0  其他为高
	 P2 = Y7;
     _nop_();
     _nop_();
     P2 = Y0;
     //Y7 为1 （此时只有Y0是0 不过Y0在板子上没有用到）
}


//位锁存器锁存
void U8suocun(void) //LED对应锁存器U8控制端LE 从高位变为低位
{
    //Y6 为0  其他为高
	P2 = Y6;
    _nop_();
	_nop_();
	P2 = Y0;
    //Y6 为1 （此时只有Y0是0 不过Y0在板子上没有用到）
}

//主函数
void main(void)
{ 
 
	TMOD |= 0x01;  //配置定时器0工作模式 16位寄存器模式
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;
    ET0 = 1; //打开定时器0中断
    TR0 = 1;  //启动定时器0
    while(1)
    {
		
    }
	
}

//定时器中断服务函数
void isr_timer_0(void)  interrupt 1 //默认中断优先级 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;//定时器重载 
	display();  //5ms执行一次
}

//显示函数
void display(void)
{   
   P0=wei[i];
   U8suocun();//送位数据和位锁存
   P0=duan[i+1];
   U7suocun();//送段数据和段锁存
   i++;
   if(i>=8)
	   i=0;	
}