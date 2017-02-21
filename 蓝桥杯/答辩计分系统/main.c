#include <reg52.h>
#include "tools.h"

#define uint unsigned int  //宏定义
#define uchar unsigned char 

//数码管字形表以及位选信号
                      // 0   1     2    3    4   5      6    7    8    9    10  11 12-c  13   14    15   -   mie   s
code uchar duan[19] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0xff,0x92};
code uchar wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff}; //最后全亮   

//数码管显示数据存储数组，显示的内容统一存放在该数组
uchar temp[8]={0,0,0,0,0,0,0,0};  //显示数据寄存在temp数组中

//全局变量定义
uchar secs = 0,mins = 1;    //倒计时10分
uint value = 0; //按键值存储
uint flag = 0;  //状态标示
uint average=0; //平均分

void beef(uint); //蜂鸣器函数声明

//定时器0中断初始化
 void init()
{	  
  	TMOD=0x01; //定时器0和定时器1都是方式1,16位定时器  
	ET0=1;     //使能定时器0
	TR0=0;	   //定时器0关，等待输入学号按确认后开启
	TH0=(65535-50000)/255;	  //定时器0高位装初值
	TL0=(65535-50000)%255;;	  //定时器0低位装初值
	EA=1;      //开总中断
 }

//定时器0终端服务函数
void time0()interrupt 1		//定时器0 服务
{	
    uchar count;
 	TH0=(65535-50000)/255;	  //定时器0高位装初值
	TL0=(65535-50000)%255;;	  //定时器0低位装初值
	count++;
	if(count==20){		  // 计时1s
			count=0;
			secs--;
		}
	if(secs>60)
		{
			secs = 59;
			mins--;
		}
	if(secs==0&&mins==0){	 //	时间到，蜂鸣器报警
			display(0xc0,0xff);  //数码管全部显示0
			beef(3);   //蜂鸣器响3声
			flag=4;    //状态标志为4，标志计时结束
			secs=0,mins=1; //计时复位
			TR0=0;     //关闭定时器0计时
	    }
}

//蜂鸣器程序，直接调用，蜂鸣器响 a次
void beef(uint a)
{
	while(a){
		P0=P0|0x40;  //P0口送蜂鸣器“发声”控制信号
		U9_beefcontrol();  //蜂鸣器控制开关，将控制信号送入锁存器，使蜂鸣器发声
		delay(500);  //蜂鸣器发声500ms
		P0=P0&0xbf;  //关蜂鸣器控制信号
		U9_beefcontrol();  //开关，执行蜂鸣器关闭
		delay(500);  
		a--;
	}
	
}

//数码管全局显示函数
void display_all(void)
{
	uint i;
	for(i=0;i<8;i++){  //对1-8位数码管交替扫描
		display(duan[temp[i]],wei[i]); //送段选、位选数据
	}
}

//主函数
void main(void)
{
	init(); //计时器中断初始化
	P0=P0&0xbf;  //关蜂鸣器
	U9_beefcontrol(); //蜂鸣器开关，送入控制信号
	while(1){
		value = read_key16(); //读取按键值，没有按键按下，value=0xff
		display_all();  //数码管全局显示

		//flag=0，第一步，监测按键是否按下
		if(flag==0&&value!=0xff){ //有按键按下，即学号第一位数值
			temp[0] = value; //读取学号第一位
			flag++;  //flag=1
			value=0xff;  //键值还原
		}
		//flag=1，第二步，监测学号第二位是否输入
		if(flag==1&&value!=0xff){ //有按键按下，学号第二位输入
			temp[1] = value; //读取学号第2位
			flag++;   //flag=2
			value=0xff; 
		}
		//flag=2，学号输入完毕，等待确认
		if(flag==2&&value==15){  //学号输入完毕，按下确认按键
			temp[2]=17;  //三四两位数码管熄灭
			temp[3]=17;  
			flag++;  //flag=3
			TR0=1; //开启定时器0中断，计时开始
			value=0xff;  
			P0=0xfe; //led亮
			U4_LED(); //led开关
		}
		//计时过程中，数码管显示计时数据
		if(TR0==1){
			temp[4]=mins/10; //分钟计时十位
			temp[5]=mins%10; //分钟计时个位
			temp[6]=secs/10;
			temp[7]=secs%10;
		}
		//监测计时是否完毕，或者选手提前陈述完毕（按下“结束--14”按键）
		if((flag==3&&value==14)||(flag==4)){  //计时结束，或者按下“结束”
			TR0=0;    //停止计时
			secs=0;mins=1;  //计时还原
			temp[4]=16; //显示 -
			temp[5]=16;
			temp[7]=16;
			temp[2]=16;
			temp[3]=0;  //数码管显示0，等待打分
			temp[6]=0;  //数码管显示0，等待打分
			flag=5;  //flag=5，状态标志，标示进入打分环节
			value=0xff;
			P0=0xf7; //led亮
			U4_LED();
		}
		//第一个教师打分
		if(flag==5&&value!=0xff){
			temp[6]=value;  //读取第一个分数，在第七个数码管显示
			flag++;   //flag=6，标示第一位老师打分完毕
			value=0xff;
		}
		//第二个教师打分	
		if(flag==6&&value!=0xff){
			temp[3]=value;  //读取第二个分数，在第四个数码管显示
			flag++; // flag=7，标示第二个老师打分完毕
			value=0xff;
		}
		//教师打分完毕，等待确认
		if(flag==7&&value==15){  //打分完毕，按下确认
			average=(temp[3]+temp[6])/2+0.5;  //两个成绩四舍五入
			temp[2]=17; //熄灭
			temp[3]=18; //s
			temp[4]=12; //c
			temp[5]=0;  //o
			temp[6]=16; //-  最终显示 “SCO-分数”的字形
			temp[7]=average;  //最后一位数码管显示最终成绩
			value=0xff;  //键值还原
			flag++;  //flag=8，标示选手答辩完毕
			P0=0xbf; //led亮
			U4_LED();
		}
		//选手打分完毕，是否进入下一位答辩？（是否按下“重置”）
		if(flag==8&&value==14){ //按下按键，进入下一轮答辩
			temp[0]=0;temp[1]=0;  //数码管显示数组内容清零
			temp[2]=0;temp[3]=0;
			temp[4]=0;temp[5]=0;
			temp[6]=0;temp[7]=0;
			flag=0;   //标志位清零
			P0=0xff; //led灭
			U4_LED();
		}	
	}
}
	



