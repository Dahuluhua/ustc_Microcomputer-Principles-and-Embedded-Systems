#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "TIM.h"
#include "LED.h"
#include "KEY.h"

u8 DutyCycle=0,flag1=0,flag2=0,flag3=0;	//定义PWM波占空比，设定范围：0-100

void TIM3_Init(u16 arr,  u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure; 
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM_TimeBaseInitStructure.TIM_Period = arr; //??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);// ??????? TIM3 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //?????? 3 ????
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //??? 3 ??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //????? 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //???? 3 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);// ????NVIC
	
	TIM_Cmd(TIM3,ENABLE); //?????? 3
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET) //判断定时器3（TIM3）是否发生计数溢出中断（TIM_IT_Update）
	{
		if(flag3 == 0){
			if(KEY0 == 0)	flag1 = (flag1+1)%3;	//按键1按下时，flag1发生变化，控制亮灯
			if(KEY1 == 0)	flag2 = (flag2+1)%3;	//按键2按下时，flag2发生变化，控制占空比（DutyCycle）变化速度
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//清除定时器3（TIM3）的计数溢出中断（TIM_IT_Update）标志。如未清除，将重复进入此中断服务函数
		}
		if(KEY0 == 0||KEY1 == 0) flag3=1;
		else if(KEY0==1&&KEY1==1) flag3=0;
	}
}

void TIM4_Init(u16 arr,  u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure; 
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_TimeBaseInitStructure.TIM_Period = arr; //??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;	//?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);// ??????? TIM3 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //?????? 3 ????
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //??? 3 ??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //????? 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //???? 3 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);// ????NVIC
	
	TIM_Cmd(TIM4,ENABLE); //?????? 3
}

u8 count=0;
u8 control_dir=1;

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET) //TIM3????
	{
		if(count==100) {
			count=0;
			if(control_dir==1){
				DutyCycle+=(flag2+1);
				if(DutyCycle>=100) 
					control_dir=0;
			}
			if(control_dir==0){
				DutyCycle-=(flag2+1);
				if(DutyCycle<=0) 
					control_dir=1;
			}
		}
		else 
			count++;
		switch(flag1){
			case 0:
			
				if(count<DutyCycle) {
					LED1 = 0;
					LED2 = 0;
					LED3 = 1;
				}
				else {
					LED1 = 0;
					LED2 = 0;
					LED3 = 0;
				}
				break;
			case 1:
			
				if(count<DutyCycle) {
					LED1 = 0;
					LED2 = 1;
					LED3 = 0;
				}
				else {
					LED1 = 0;
					LED2 = 0;
					LED3 = 0;
				}
				break;
			case 2:
			
				if(count<DutyCycle) {
					LED1 = 1;
					LED2 = 0;
					LED3 = 0;
				}
				else {
					LED1 = 0;
					LED2 = 0;
					LED3 = 0;
				}
				break;
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);	//???????
}
