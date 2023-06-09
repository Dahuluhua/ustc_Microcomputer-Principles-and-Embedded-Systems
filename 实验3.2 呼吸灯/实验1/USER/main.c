#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "LED.h"
#include "DIP.h"
#include "TIM.h"
#include "PWM.h"

u32 led0pwmval = 0;
u8 flag = 0;

int main(void)
{
	delay_init(168); 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	TIM2_PWM_Init(3000,0);
	LED_Init();
//	

while(1) 
	{ 		
		if(flag == 0){
			led0pwmval+=50;
		}
		else if(flag == 1){
			led0pwmval-=50;
		}
		if(led0pwmval == -50){
			flag = 0;
			led0pwmval = 0;
		}
		else if(led0pwmval == 3050){
			flag = 1;
			led0pwmval=3000;
		}
		TIM_SetCompare3(TIM2,led0pwmval);	
		delay_ms(5);
	}

}

