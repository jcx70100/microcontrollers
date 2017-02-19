#ifndef __tools_h__
#define __tools_h__

#include "tools.h"

//#include <reg52.h>
#include <intrins.h>

//延时函数
void delay(unsigned int x)
{
	unsigned int i,j;
	for(i=x;i>0;i--){
		for(j=120;j>0;j--);
	}
}

//读取矩阵键盘键值 返回的就是按键的对应值 0-15
bit key_re;
unsigned char key_press;
unsigned char key_value;
unsigned char read_key16(void)
{
    unsigned char key_temp;
    static unsigned char col;
    
	P3 = 0xf0;    
    key_temp = (P3&0xf0);
     
    if(key_temp != 0xf0) //有按键按下
		{key_press++;
				//delay(10);
		}
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

//U9，蜂鸣器等驱动控制Y5*******************************************
void U9_beefcontrol(void)
{
    P2=P2&0x1f;
    P2=P2|0xa0;
    _nop_();
    _nop_();
    P2=P2&0x1f;
}



//段锁存器和位锁存器LE控制********************************************
//sbit  HC138A = P2^5;
//sbit  HC138B = P2^6;
//sbit  HC138C = P2^7;  
//数码管段选开关
void U7_duan(void)
{
	/*HC138C=1;
	HC138B=1;
	HC138A=1;*/
	P2=P2&0x1f;  // xxxx xxxx & 0001 1111= 000x xxxx
    P2=P2|0xe0;  //只影响高3位用于38译码  000x xxxx | 1110 0000 = 111x xxxx
	_nop_();
	_nop_();
	/*HC138C=0;
	HC138B=0;
	HC138A=0;*/
	P2=P2&0x1f;  
}
//数码管位选开关
void U8_wei(void)
{
	/*HC138C=1;
	HC138B=1;
	HC138A=0;*/
	P2=P2&0x1f;
    P2=P2|0xc0;
	_nop_();
	_nop_();
	/*HC138C=0;
	HC138B=0;
	HC138A=0;*/
	P2=P2&0x1f;
}

//数码管显示函数
void display(unsigned char duan, unsigned char wei)
{
    P0=duan;
    U7_duan();
    P0=wei;
    U8_wei();
    delay(2); //决定刷新频率
}


//LED的U4锁存器LE控制*******************8888
void U4_LED(void)
{
	P2=P2|0x80;   //000x xxxx  | 1000 0000 = 100x xxxx--> Y4
	_nop_();   // wait  ,
	P2=P2&0x1f;  // 100x xxxx & 0001 1111 = 000x xxxx
}

#endif