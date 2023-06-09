#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "USART.h"

u8 USART_RX_BUF[USART_REC_LEN];     
u16 USART_TX_EN=1; 
u16 USART_RX_STA=0; 

void uart1_init(u32 bound){
   GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); 	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); 	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART1, &USART_InitStructure); 	
  
	
		
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;	 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);
	USART_Cmd(USART1, ENABLE);	
}
 void USART1_IRQHandler(void)                
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		Res =USART_ReceiveData(USART1);	
		//?????
		//????USART_RX_STA++;
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);		
	}		 
} 
