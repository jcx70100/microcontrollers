//实现8个led流水灯从右往左单个点亮，实现流水灯，最后全部交替闪烁两次

#include <stc15f2k60s2.h>
#include <key.h>
//#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
#define delaytime 300


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
	uint i;
	HC138C = 0;
	HC138B = 0;
	HC138A = 0;
	while(1){
		P0 = 0xff;
		LED_HC138();
		delay(delaytime);
		for(i=0;i<8;i++){
			P0 = _crol_(0xfe,i);
			LED_HC138();
			delay(delaytime);
		}
		P0 = 0xff;
		LED_HC138();
		delay(delaytime);
		P0 = 0x00;
		LED_HC138();
		delay(delaytime);
		P0 = 0xff;
		LED_HC138();
		delay(delaytime);
		P0 = 0x00;
		LED_HC138();
		delay(delaytime);
	}
}