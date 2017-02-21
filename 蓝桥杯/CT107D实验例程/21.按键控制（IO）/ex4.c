/*******************************************************************************  
* 文件名称：按键控制实验
* 实验目的：1.掌握单片机IO口操作的基本方法 
*           2.掌握C51关键字"sbit"的用法
*           2.掌握单片机常见外围驱动电路的设计方法 
* 程序说明：使用程序前，将跳线J5调整为BTN模式独立按键模式  J13选择为IO模式  带软件消抖
   扫描的方法处理S4 S5 S6 S7的按键操作。
* 日期版本：2015 NUAA  
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "intrins.h"

/** 独立按键接口 */
sbit S7  = P3^0;
sbit S6  = P3^1;
sbit S5  = P3^2;
sbit S4  = P3^3;

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
   HC138C = 0; //Y4 为1 （此时只有Y0是0 不过Y0在板子上没有用到）
  
}



//主函数
void main(void)
{    
	unsigned char i;
	//把要显示的方式写成数组，可以实现花样流水灯
	char temp[4] = {0x7f,0xbf,0xdf,0xef}; //把要点亮的方式写成数组
	
    HC138A = 0;
    HC138B = 0;
    HC138C = 0; //初始化 
	S4 = 1;
    S5 = 1;
    S6 = 1;
    S7 = 1;
	while(1)
    {
        if(S7 == 0)
        {
	      delay(5);//小段延时 进行消抖
          if(S7 == 0)
		  {
			   P0 = temp[0];
		       U6suocun();
          }			  	
        }
        if(S6 == 0)
        {
          delay(5);//小段延时 进行消抖
          if(S6 == 0)
		  {
			   P0 = temp[1];
		       U6suocun();
          }		
        }
        if(S5 == 0)
        {
          delay(5);//小段延时 进行消抖
          if(S5 == 0)
		  {
			   P0 = temp[2];
		       U6suocun();
          }		  
        }
        if(S4 == 0)
        {
           delay(5);//小段延时 进行消抖
          if(S4 == 0)
		  {
			   P0 = temp[3];
		       U6suocun();
          }		
        }

    }
}