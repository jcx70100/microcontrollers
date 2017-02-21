//实现8个led交替亮灭

#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

sbit HC138A = P2^5;
sbit HC138B = P2^6;
sbit HC138C = P2^7;

void delay(uint x)
{
	uint i,j;
	for(i=x;i>0;i--){
		for(j=110;j>0;j--);
	}
}


void LED_HC138(void)
{
	HC138C = 1;
	HC138B = 0;
	HC138A = 0;
	_nop_();
	HC138C = 0;
}

void main(void)
{
	HC138C = 0;
	HC138B = 0;
	HC138A = 0;
	while(1){
		P0 = 0xff;
		LED_HC138();
		delay(200);
		P0 = 0x00;
		LED_HC138();
		delay(200);
	}
}