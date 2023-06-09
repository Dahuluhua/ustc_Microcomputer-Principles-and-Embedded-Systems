#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "LED.h"
#include "KEY.h"
#include "EXTI.h"
#include "DIP.h"
#include "string.h"
#include "12864.h"
#include "usart.h"

int main(void)
{
	char USART_SendBuf[]="Hello!";
  int i;  
  int Len = strlen(USART_SendBuf);	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
  LCD_GPIO_Init();
	LCD_Init();
	uart1_init(115200);
	
	while(1){
		delay_ms(2000);
		if(USART_TX_EN)
		{
			for(i=0;i<Len;i++)
			{
				USART_SendData(USART1, USART_SendBuf[i]); 				
				while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
			}
			USART_TX_EN=0;
		}
		//?????
		if(USART_RX_STA==Len)
			LCD_Display_Words(0,0,USART_RX_BUF);
	}

}


