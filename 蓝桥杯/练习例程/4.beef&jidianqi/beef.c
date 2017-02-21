//实现四个按键控制蜂鸣器和继电器，按下不同的案件控制蜂鸣器和继电器启动次数

//注意，键盘的跳线插口要改变
#include <reg52.h>
#include <intrins.h>
#include <self.h>
#define uint unsigned int 
#define uchar unsigned char

sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;

char temp[4] = {0x40,0x00,0x10,0x00}; //对应分别是打开蜂鸣器 关闭蜂鸣器 打开继电器 断开继电器


void main()
{
	uint i=2,j;
	S7=1;S6=1;S5=1;S4=1;
	P2=P2&0x1f;
	while(1)
    {
        if(S7 == 0)
        {
	      delay(5);//小段延时 进行消抖
          if(S7 == 0){
          	i=1;
          }	  	
        }
        if(S6 == 0)
        {
          delay(5);//小段延时 进行消抖
          if(S6 == 0){
          	i=2;
          }
        }
        if(S5 == 0)
        {
          delay(5);//小段延时 进行消抖
          if(S5 == 0){
          	i=3;
          }
        }
        if(S4 == 0)
        {
           delay(5);//小段延时 进行消抖
          if(S4 == 0){
          	i=4;
          }	
        }
        for(j=0;j<i;j++){
            P0 = temp[0];
					 U9_control();
					delay(300);
					  P0 = temp[2];
            U9_control();
            delay(300);
            P0 = temp[1];
					 U9_control();
					delay(300);
					  P0 = temp[3];
            U9_control();
            delay(300);
        }
        i=0;
			}
}