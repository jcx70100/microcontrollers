//利用定时器中断实现数码管的动态扫描

#include <reg52.h>
#include <intrins.h>
#include <self.h>
#define uint unsigned int
#define uchar unsigned char
//#define delay_time 3

code unsigned char duan[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};
uchar i=0;
void display(void);
void main()
{
	TMOD|=0x01;
	TH0=(65536-2000)/256;
	TL0=(65536-2000)%256;
	EA=1;
	ET0=1;
	TR0=1;

	while(1){
		
		
	}
}

void TIME0(void) interrupt 1
{
	//EA=0;
	//TR0=0;
	TH0=(65536-2000)/256;
	TL0=(65536-2000)%256;
	display();
	//TR0=1;
	//EA=1;
}

void display(void)
{
		P0=duan[i];
		U7_duan();
		P0=wei[i];
		U6_wei();
		i++;
		if(i>=8){
			i=0;
			/*P0=duan[15];
			U7_duan();
			P0=wei[8];
			U6_wei();
			delay(delay_time);
		}*/
	}
	
}