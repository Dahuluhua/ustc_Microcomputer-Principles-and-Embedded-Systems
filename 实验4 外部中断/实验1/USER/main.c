#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "LED.h"
#include "KEY.h"
#include "EXTI.h"
#include "DIP.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);   	
	LED_Init();				  
	KEY_Init();
	EXTI0_Init();
	EXTI3_Init();
	DIP_Init();       
	LED0=1;	     
	LED7=1;		
	while(1)
	{}
}


