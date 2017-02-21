/*******************************************************************************  
* 文件名称：点阵屏幕显示实验
* 实验目的：1.掌握点阵屏动态扫描的基本原理
*           2.掌握51单片机定时器工作模式和配置方法
*           3.掌握keil uvision集成开发环境下，中断服务函数设计方法
* 程序说明：无  8X8点阵屏只能显示数字和简单字。

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

//汉字的取模编码: 横向取模，1是点亮, 低位在前面  字节倒序
code unsigned char zimo[8] = {0x7E,0x5A,0x3C,0x18,0x18,0x18,0x3C,0xFF};


//行选： 从上到下，上面为低位。 0是选中。
code unsigned char hang[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


unsigned char i = 0;
void display(void);
void U7suocun(void);
void U8suocun(void);


//字模锁存器锁存
void U7suocun(void) //LED对应锁存器U7控制端LE 从高位变为低位
{
     //Y7 为0  其他为高
	 P2 = Y7;
     _nop_();
     _nop_();
     P2 = Y0;
     //Y7 为1 （此时只有Y0是0 不过Y0在板子上没有用到）
}


//行选锁存器锁存
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
  
   P0=zimo[i];
   U7suocun();//字模锁存操作
   P0=hang[i];
   U8suocun();//行锁存操作
   i++;
   if(i>=8)
	   i=0;	
}