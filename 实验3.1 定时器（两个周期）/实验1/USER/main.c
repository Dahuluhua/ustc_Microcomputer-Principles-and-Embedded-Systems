#include "stm32f4xx.h"
#include "delay.h"//��ʱ�������ڵ�ͷ�ļ�
#include "LED.h"
#include "DIP.h"
#include "TIM.h"

int main(void)
{
	delay_init(168);	//???????
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//??????????? 2
	LED_Init();
	DIP_Init();
	TIM3_Init(83, 49999);
	while(1)
	{
		
	}
}

