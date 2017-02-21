/*******************************************************************************  
* 文件名称：数码管控制实验
* 实验目的：1.掌握数码管动态扫描的基本原理,掌握数码管消除“鬼影”的方法
*           2.掌握51单片机定时器工作模式和配置方法
*           3.掌握keil uvision集成开发环境下，中断服务函数设计方法
* 程序说明：无
* 日期版本：2015-8   NUAA 
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

                               //0    1    2    3    4    5    6    7    8    9    a    b   c    d    e    f
code unsigned char duan[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};


bit key_re;
unsigned char key_press;
unsigned char key_value;

bit key_flag;
unsigned char intr;

unsigned char read_keyboard(void);
void key_proc(unsigned char key);
void U6suocun(void);


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
    unsigned char key_temp = 0xff;
    
    TMOD |= 0x01;//配置定时器0工作模式 模式1 16位计数器
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;  //打开总中断
    ET0 = 1; //打开定时器0中断
    TR0 = 1; //启动定时器0
	
    while(1)
    {
        if(key_flag)
        {
            key_flag = 0;
            key_temp = read_keyboard();//20ms 进来扫描一次
        } 
        key_proc(key_temp);//对应按键按下的操作      
        key_temp = 0xff;//清除旧键值
    }
}


//定时器中断服务函数
void isr_timer_0(void)  interrupt 1  //默认中断优先级 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256; //定时器重载 
     
	if(++intr == 10)  //2ms执行一次
	{
        intr = 0;
		key_flag = 1;//20ms按键扫描标志位置1
    }
}



//读取矩阵键盘键值 返回的就是按键的对应值 0-15
unsigned char read_keyboard(void)
{
    unsigned char key_temp;
    static unsigned char col;
    
	P3 = 0xf0;    
    key_temp = (P3&0xf0);
     
    if(key_temp != 0xf0) //有按键按下
        key_press++;
	else
		key_press = 0;//抖动
	
    if(key_press == 3) //连续三次都是有按键按下 则确定为有按键按下
    {
		key_press = 0;
		key_re = 1;
		switch(key_temp)
        {
            case 0x70:
                col = 1;  //第一列按键按下
                break;                
            case 0xb0:
                col = 2;  //第二列按键按下
                break;    
            case 0xd0:
                col = 3;  //第三列按键按下
                break;    
            case 0xe0:
                col = 4;  //第四列按键按下
                break;
        }
        P3 = 0x0f;
        key_temp = (P3&0x0f);
		switch(key_temp)
        {
            case 0x0e:
                key_value = (col-1);   //第一行按键按下
                break;                
            case 0x0d:
                key_value = (3+col);   //第二行按键按下
                break;    
            case 0x0b:
                key_value = (7+col);   //第三行按键按下
                break;    
            case 0x07:
                key_value = (11+col);  //第四行按键按下
                break;
        }
    }
    //连续三次检测到按键被按下，并且该按键已经释放
	P3 = 0x0f;
	key_temp = (P3&0x0f);
    if((key_re == 1) && (key_temp == 0x0f))
    {
        key_re = 0;
        return key_value;
    }
    return 0xff;  //无按键按下或被按下的按键未被释放 
}


//按键处理函数 
void key_proc(unsigned char key)
{
   
	if(key != 0xff)
	{
		P0=wei[0];
        U8suocun();//送位数据和位锁存
        P0=duan[key];
        U7suocun();//送段数据和段锁存
    }
	
}