#include "stm32f4xx.h"
#include "delay.h"//��ʱ�������ڵ�ͷ�ļ�
#include "KEY.h"

void KEY_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;   //GPIO��ʼ���ṹ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOG��GPIODʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_Pin_0);//LED1,LED2,LED3,LED4,LED5
}
