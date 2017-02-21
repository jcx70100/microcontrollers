/*******************************************************************************  
* �ļ����ƣ�����ܿ���ʵ��
* ʵ��Ŀ�ģ�1.��������ܶ�̬ɨ��Ļ���ԭ��,�����������������Ӱ���ķ���
*           2.����51��Ƭ����ʱ������ģʽ�����÷���
*           3.����keil uvision���ɿ��������£��жϷ�������Ʒ���
* ����˵������
* ���ڰ汾��2015-8   NUAA 
*******************************************************************************/

#include "reg52.h"  //����51��Ƭ�����⹦�ܼĴ���
#include "intrins.h"

sbit  HC138A = P2^5;
sbit  HC138B = P2^6;
sbit  HC138C = P2^7;               

//������P25 P26 P27�仯��ӦʹY0-Y7Ϊ0
#define  Y0   0x1f 
#define  Y1   0x3f     
#define  Y2   0x5f  
#define  Y3   0x7f 
#define  Y4   0x9f 
#define  Y5   0xbf 
#define  Y6   0xdf   
#define  Y7   0xff   

                               //0    1    2    3    4    5    6    7    8    9    a    b   c    d    e    f
code unsigned char duan[16] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
code unsigned char wei[9] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};


bit key_re;
unsigned char key_press;
unsigned char key_value;

bit key_flag;
unsigned char intr;

unsigned char read_keyboard(void);
void key_proc(unsigned char key);
void U6suocun(void);


//������������
void U7suocun(void) //LED��Ӧ������U7���ƶ�LE �Ӹ�λ��Ϊ��λ
{
     //Y7 Ϊ0  ����Ϊ��
	 P2 = Y7;
     _nop_();
     _nop_();
     P2 = Y0;
     //Y7 Ϊ1 ����ʱֻ��Y0��0 ����Y0�ڰ�����û���õ���
}


//λ����������
void U8suocun(void) //LED��Ӧ������U8���ƶ�LE �Ӹ�λ��Ϊ��λ
{
    //Y6 Ϊ0  ����Ϊ��
	P2 = Y6;
    _nop_();
	_nop_();
	P2 = Y0;
    //Y6 Ϊ1 ����ʱֻ��Y0��0 ����Y0�ڰ�����û���õ���
}


//������
void main(void)
{ 
    unsigned char key_temp = 0xff;
    
    TMOD |= 0x01;//���ö�ʱ��0����ģʽ ģʽ1 16λ������
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256;  
    EA = 1;  //�����ж�
    ET0 = 1; //�򿪶�ʱ��0�ж�
    TR0 = 1; //������ʱ��0
	
    while(1)
    {
        if(key_flag)
        {
            key_flag = 0;
            key_temp = read_keyboard();//20ms ����ɨ��һ��
        } 
        key_proc(key_temp);//��Ӧ�������µĲ���      
        key_temp = 0xff;//����ɼ�ֵ
    }
}


//��ʱ���жϷ�����
void isr_timer_0(void)  interrupt 1  //Ĭ���ж����ȼ� 1
{
    TH0 = (65536-2000)/256;
    TL0 = (65536-2000)%256; //��ʱ������ 
     
	if(++intr == 10)  //2msִ��һ��
	{
        intr = 0;
		key_flag = 1;//20ms����ɨ���־λ��1
    }
}



//��ȡ������̼�ֵ ���صľ��ǰ����Ķ�Ӧֵ 0-15
unsigned char read_keyboard(void)
{
    unsigned char key_temp;
    static unsigned char col;
    
	P3 = 0xf0;    
    key_temp = (P3&0xf0);
     
    if(key_temp != 0xf0) //�а�������
        key_press++;
	else
		key_press = 0;//����
	
    if(key_press == 3) //�������ζ����а������� ��ȷ��Ϊ�а�������
    {
		key_press = 0;
		key_re = 1;
		switch(key_temp)
        {
            case 0x70:
                col = 1;  //��һ�а�������
                break;                
            case 0xb0:
                col = 2;  //�ڶ��а�������
                break;    
            case 0xd0:
                col = 3;  //�����а�������
                break;    
            case 0xe0:
                col = 4;  //�����а�������
                break;
        }
        P3 = 0x0f;
        key_temp = (P3&0x0f);
		switch(key_temp)
        {
            case 0x0e:
                key_value = (col-1);   //��һ�а�������
                break;                
            case 0x0d:
                key_value = (3+col);   //�ڶ��а�������
                break;    
            case 0x0b:
                key_value = (7+col);   //�����а�������
                break;    
            case 0x07:
                key_value = (11+col);  //�����а�������
                break;
        }
    }
    //�������μ�⵽���������£����Ҹð����Ѿ��ͷ�
	P3 = 0x0f;
	key_temp = (P3&0x0f);
    if((key_re == 1) && (key_temp == 0x0f))
    {
        key_re = 0;
        return key_value;
    }
    return 0xff;  //�ް������»򱻰��µİ���δ���ͷ� 
}


//���������� 
void key_proc(unsigned char key)
{
   
	if(key != 0xff)
	{
		P0=wei[0];
        U8suocun();//��λ���ݺ�λ����
        P0=duan[key];
        U7suocun();//�Ͷ����ݺͶ�����
    }
	
}