//实现不同的按键按下显示不同的led点亮过程

#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define delay_time 300

sbit HC138A = P2^5;
sbit HC138B = P2^6;
sbit HC138C = P2^7;

sbit S7 = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

void delay(uint);
void U6(void);
void key_scan(void);

void delay(uint x)
{
	uint i,j;
	for(i=x;i>0;i--){
		for(j=110;j>0;j--);
	}
} 

void U6(void)
{
	HC138A=0;
	HC138B=0;
	HC138C=0;
	_nop_();
	HC138C=1;
}

void main()
{
	HC138C=0;HC138B=0;HC138A=0;
	while(1){
		key_scan();
	}
}

void key_scan(void)
{
	uint i=0,j;
	if(S7==0) i=1;
	if(S6==0) i=2;
	if(S5==0) i=3;
	if(S4==0) i=4;
	P0 = 0xff;
	for(j=0;j<i;j++){
		P0 = 0x00;
		U6();
		delay(delay_time);
		P0 =0xff;
		U6();
		delay(delay_time);
	}
}