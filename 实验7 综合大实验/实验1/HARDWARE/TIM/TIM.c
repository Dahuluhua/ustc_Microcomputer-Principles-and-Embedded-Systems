#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "TIM.h"
#include "LED.h"
#include "KEY.h"

u8 DutyCycle=0,flag1=0,flag2=0,flag3=0;	//����PWM��ռ�ձȣ��趨��Χ��0-100

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
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET) //�ж϶�ʱ��3��TIM3���Ƿ�����������жϣ�TIM_IT_Update��
	{
		if(flag3 == 0){
			if(KEY0 == 0)	flag1 = (flag1+1)%3;	//����1����ʱ��flag1�����仯����������
			if(KEY1 == 0)	flag2 = (flag2+1)%3;	//����2����ʱ��flag2�����仯������ռ�ձȣ�DutyCycle���仯�ٶ�
			
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//�����ʱ��3��TIM3���ļ�������жϣ�TIM_IT_Update����־����δ��������ظ�������жϷ�����
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
