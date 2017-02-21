//实现了由矩阵键盘控制，8位数码管同时显示按键数值
#include <reg52.h>
#include <intrins.h>
#include <self.h>
#define uint unsigned int
#define uchar unsigned char
#define delay_time 400

code unsigned char duan[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};

void main()
{
	uchar value=0xff;
	while(1){
		value=read_key16();
		if(value!=0xff){
			P0=duan[value];
			U7_duan();
			P0=wei[8];
			U6_wei();
			//delay(delay_time);
		}
		//value=0xff;
	}
}