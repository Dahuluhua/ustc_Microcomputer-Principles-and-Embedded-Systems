#include "stm32f4xx.h"
#include "delay.h"//��ʱ�������ڵ�ͷ�ļ�
#include "LED.h"
#include "DIP.h"

int main(void)
{ 
	LED_Init();		       //��ʼ��LED�˿�
	delay_init(168);     //��ʼ����ʱ����
	DIP_Init();
	while(1)
	{
		/*LED0 = 1;
		delay_ms(500);
		LED0 = 0;
		delay_ms(500);*/
		if(DIP0 == 1) {			
			LED0 = 1;
		}
		else if(DIP0 == 0){
			 LED0 = 0;
		}
		if(DIP1 == 1) LED1 = 1;
		else LED1 = 0;
		if(DIP2 == 1) LED2 = 1;
		else LED2 = 0;
		if(DIP3 == 1) LED3 = 1;
		else LED3 = 0;
		if(DIP4 == 1) LED4 = 1;
		else LED4 = 0;
		if(DIP5 == 1) LED5 = 1;
		else LED5 = 0;
		if(DIP6 == 1) LED6 = 1;
		else LED6 = 0;
		if(DIP7 == 1) LED7 = 1;
		else LED7 = 0;		
 	}
}

