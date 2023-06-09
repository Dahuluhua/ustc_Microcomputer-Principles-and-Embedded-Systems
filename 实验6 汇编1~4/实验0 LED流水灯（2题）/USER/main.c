#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
/*
void LED_Init(void); 		

#define ON   Bit_SET     //GPIO的布尔变量，用于GPIO_WriteBit函数
#define OFF  Bit_RESET   //GPIO的布尔变量，用于GPIO_WriteBit函数

#define LED0(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_11, x)//写IO口状态，0/1
#define LED1(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_10, x)
#define LED2(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_9, x)
#define LED3(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_7, x)
#define LED4(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_3, x)
#define LED5(x)  GPIO_WriteBit(GPIOG, GPIO_Pin_2, x)
#define LED6(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_13, x)
#define LED7(x)  GPIO_WriteBit(GPIOD, GPIO_Pin_12, x)
*/
extern void TestAsm(void);
extern void strcopy(char*d,char*s);
int main ()  
{
	//TestAsm();
	char * srcstr = "0123456";
	char dstr[] = "abcdefg";
	strcopy(dstr,srcstr);
	
	return 0;
}
/*
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;   //GPIO初始化结构体
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|
								RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOG、GPIOD时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_9 | GPIO_Pin_2 | GPIO_Pin_3;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_2 | GPIO_Pin_3);//LED1,LED2,LED3,LED4,LED5

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_12 | GPIO_Pin_13;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD, GPIO_Pin_7 |GPIO_Pin_12|GPIO_Pin_13);  //LED6,LED7		 
}*/

