/*******************************************************************************  
* 文件名称：LED移位控制实验
* 实验目的：掌握单片机IO口操作的基本方法
* 程序说明：无
* 日期版本：2012-9-3/V1.0a 
*******************************************************************************/

#include "reg52.h"  //定义51单片机特殊功能寄存器
#include "intrins.h"

//延时函数
void delay(void)
{
    unsigned char i,j,k;
    for(i=0; i<10; i++)
    {
        for(j=0; j<20; j++)
        {
            for(k=0; k<248; k++);
        }
    } 
}

//主函数
void main(void)
{
    unsigned char i;
    
    while(1)
    {
		for(i=0; i<8; i++)
		{
			P2 = ((P2 &0x1f)|0x80);
			P0 = 0xfe<<i;  //左移i位
			P2 &= 0x1f;
			delay();
		}
    }
}