//由按键控制，按下按键后，对应的数码管显示对应的数
#include "reg52.h"
#include "lq.h"
#include "intrins.h"
#define uint unsigned int
#define uchar unsigned char
#define delaytime 300

void led_shanshuo(void);

void main(void)
{
	//uint i;
	uchar number;
	P2=0x1f;  //38 restart
	while(1){
		  
		  number=read_key16();
			leds_control(number,number);
		  delay(300);
		  
		
	}
}

