#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "EXTI.h"
#include "LED.h"

void EXTI0_Init(void)
{
	 NVIC_InitTypeDef   NVIC_InitStructure;
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	
	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
	
   EXTI_InitStructure.EXTI_Line = EXTI_Line0;
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //????? 
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
	 EXTI_Init(&EXTI_InitStructure);
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;   
 	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	 NVIC_Init(&NVIC_InitStructure);		   
}

void EXTI0_IRQHandler(void) 
{ 
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)//?????????????     
  { 
		delay_ms(100);
    LED0 = !LED0;
		EXTI_ClearITPendingBit(EXTI_Line0);    //??LINE???????   
	}       
} 

void EXTI3_Init(void)
{
	 NVIC_InitTypeDef   NVIC_InitStructure;
	 EXTI_InitTypeDef   EXTI_InitStructure;
	 
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	
	 SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);
	
   EXTI_InitStructure.EXTI_Line = EXTI_Line3;
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //????? 
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
	 EXTI_Init(&EXTI_InitStructure);
	 NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;   
 	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
	 NVIC_Init(&NVIC_InitStructure);		   
}

void EXTI3_IRQHandler(void) 
{ 
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)//?????????????     
  { 
		delay_ms(100);
    LED7 = !LED7;
		EXTI_ClearITPendingBit(EXTI_Line3);    //??LINE???????   
	}       
} 
