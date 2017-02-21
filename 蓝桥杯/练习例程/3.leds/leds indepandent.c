//数码管逐个显示1-F
#include <reg52.h>
#include <intrins.h>
#include <self.h>
#define uint unsigned int
#define uchar unsigned char
#define delay_time 300

code unsigned char duan[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};


void main()
{
	uchar i=0;
	while(1){
		P0=duan[i%16];
		U7_duan();
		P0=wei[i%8];
		U6_wei();
		i++;
		delay(delay_time);
		/*if(i%8==0){
			P0=duan[15];
			U7_duan();
			P0=wei[8];
			U6_wei();
			delay(delay_time);
		}*/
	}
}