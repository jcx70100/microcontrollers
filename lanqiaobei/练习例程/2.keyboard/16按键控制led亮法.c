//实现不同的按键按下显示不同的led点亮过程

#include <reg52.h>
#include <intrins.h>
#include "self.h"
#define uint unsigned int
#define uchar unsigned char
#define delay_time 200

sbit HC138A = P2^5;
sbit HC138B = P2^6;
sbit HC138C = P2^7;

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

void U6(void);
void led(uchar);


void U6(void)
{
	HC138A=0;
	HC138B=0;
	HC138C=0;
	_nop_();
	HC138C=1;
}

uchar value;
void main()
{
	HC138C=0;HC138B=0;HC138A=0;
	
	while(1){
		value=read_key16()+1;
		led(value);
		value=0;
	}
}

void led(uchar x)
{
	uint j;
	P0 = 0xff;
	for(j=0;j<x;j++){
		P0 = 0x00;
		U6();
		delay(delay_time);
		P0 =0xff;
		U6();
		delay(delay_time);
	}
}