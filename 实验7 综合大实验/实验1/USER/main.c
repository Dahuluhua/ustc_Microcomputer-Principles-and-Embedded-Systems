#include "stm32f4xx.h"
#include "delay.h"//延时函数所在的头文件
#include "LED.h"
#include "KEY.h"
#include "EXTI.h"
#include "TIM.h"
#include "DIP.h"
#include "string.h"
#include "12864.h"
#include "usart.h"

//u32 led0pwmval = 0;
//u8 flag = 0;

char USART_SendBuf[]="Hello!s";
int Len;

uint8_t dips0, dips1;

int flag[2] = {-1, -1};

int main(void)
{
	char dip0[] = "DIP0!";
	char dip1[] = "DIP1!";
  int i;  
  Len = strlen(USART_SendBuf);	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
  LCD_GPIO_Init();
	LCD_Init();
  LCD_Clear();
	uart1_init(115200);
	
	LED_Init();
	TIM3_Init(49999, 71);
	TIM4_Init(99,71);
	
	DIP_Init();
	
	while(1){
		//LCD_Display_Words(2,1,"PB18061426");
		delay_ms(2000);
		if(DIP0 == 1 && DIP1 == 0){
			flag[1] = 0;
			if(flag[0]<0){
				flag[0] = 0;
				strcpy(USART_SendBuf, dip0);
				Len = strlen(USART_SendBuf);
				USART_TX_EN = 1;
				USART_RX_STA = 0;
			}
			else{
				if(flag[1]!=flag[0]){
					strcpy(USART_SendBuf, dip0);
					Len = strlen(USART_SendBuf);
					USART_TX_EN = 1;
					flag[0] = flag[1];
					USART_RX_STA = 0;
				}
			}
		}
		else if(DIP1 == 1 && DIP0 == 0){
			flag[1] = 1;
			if(flag[0]<0){
				flag[0] = 1;
				strcpy(USART_SendBuf, dip1);
				Len = strlen(USART_SendBuf);
				USART_TX_EN = 1;
				USART_RX_STA = 0;
			}
			else{
				if(flag[1]!=flag[0]){
					strcpy(USART_SendBuf, dip1);
					Len = strlen(USART_SendBuf);
					USART_TX_EN = 1;
					flag[0] = flag[1];
					USART_RX_STA = 0;
				}
			}
		}
		if(USART_TX_EN)
		{
			for(i=0;i<Len;i++)
			{
				USART_SendData(USART1, USART_SendBuf[i]); 				
				while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)!=SET);
			}
			USART_TX_EN=0;
		}
		if(USART_RX_STA==Len)
			LCD_Display_Words(0,0,USART_RX_BUF);		
	}
	/*外部中断****************************************************************************************/
	/*
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
	*/
	/*TIM2呼吸灯*************************************************************************************/
	/*
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
	*/
	/*LCD***************************************************************************************/
	/*
	unsigned char ImageData[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x07,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7F,0x80,0x00,0x00,0x00,0x00,0x18,0x0C,0x00,0x00,0x01,0x00,0x00,0x00,0x00,
0x01,0xFF,0x80,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x13,0x10,0x03,0xFE,0x00,
0x03,0xFF,0xC0,0x00,0x00,0x00,0x00,0x58,0x00,0x00,0x00,0x3F,0x30,0x1F,0xFF,0xC0,
0x03,0xFF,0xE0,0x00,0x00,0x00,0x00,0x8C,0x03,0xF0,0x00,0x7F,0xE0,0x7C,0x01,0xE0,
0x03,0xFF,0xF0,0x00,0x00,0x00,0x01,0x36,0x06,0xC0,0x00,0x5F,0xC0,0xFF,0xFC,0x60,
0x01,0xFF,0xF0,0x00,0x00,0x00,0x02,0x1B,0x0F,0x80,0x00,0xFF,0x01,0xFE,0x0F,0x30,
0x00,0xEF,0xF0,0x00,0x00,0x00,0x02,0x6D,0x9F,0x00,0x00,0x3E,0x03,0xFF,0xF1,0x90,
0x00,0xFF,0xF8,0x00,0x00,0x00,0x04,0x36,0xFE,0x00,0x01,0xFF,0x07,0xFF,0xFC,0x90,
0x00,0xEF,0xFF,0xFF,0x80,0x00,0x04,0xDB,0x7E,0x00,0x03,0xFF,0x87,0xFF,0xFC,0xD0,
0x00,0x0F,0xFF,0xFF,0xC0,0x00,0x04,0x6D,0xFC,0x00,0x07,0xFF,0x8F,0xFF,0xFE,0x50,
0x00,0x0F,0xFF,0xFF,0xE0,0x00,0x04,0x36,0xFC,0x10,0x07,0xFF,0x8F,0xFF,0xFE,0x90,
0x00,0x0F,0xFF,0xFF,0xE0,0x00,0x04,0x1B,0xF8,0x10,0x07,0xFF,0xCF,0xFF,0xFE,0x80,
0x00,0x0F,0xFF,0xFF,0xF0,0x00,0x04,0x0F,0xF8,0x10,0x07,0xFF,0xFF,0xFF,0xFA,0x00,
0x00,0x07,0xFF,0xFF,0xF0,0x00,0x04,0x07,0xF0,0x10,0x07,0xFF,0xFF,0xFF,0xFA,0x00,
0x00,0xFF,0xFF,0xFF,0xF8,0x00,0x02,0x03,0xF0,0x20,0x07,0xFF,0xFF,0xFF,0xBA,0x00,
0x00,0xFD,0xFF,0xFF,0xFC,0x00,0x02,0x03,0xF0,0x20,0x03,0xFF,0xFF,0xDF,0xB8,0x00,
0x00,0xC1,0xC0,0x3F,0xFC,0x00,0x01,0x01,0xE0,0x40,0x00,0xFF,0xFF,0xDF,0xB0,0x00,
0x00,0x81,0xC0,0x3F,0xCE,0x00,0x00,0x81,0xE0,0x80,0x00,0x7F,0xFF,0xDF,0xA0,0x00,
0x00,0x81,0x80,0x1D,0xCF,0x00,0x00,0x41,0xE1,0x00,0x00,0x3F,0xFF,0x9B,0x00,0x00,
0x01,0x83,0x80,0x1F,0xC7,0x80,0x00,0x21,0xE2,0x00,0x00,0x1F,0xFD,0xB6,0x00,0x00,
0x01,0xC3,0x00,0x0E,0xE6,0x80,0x00,0x19,0xEC,0x00,0x00,0x07,0xFE,0x20,0x00,0x00,
0x00,0xC3,0x00,0x07,0x67,0x40,0x00,0x07,0xF0,0x00,0x00,0x03,0x3E,0x00,0x00,0x00,
0x00,0x02,0x00,0x03,0xE7,0xA0,0x00,0x00,0x00,0x00,0x00,0x02,0x8E,0x00,0x00,0x00,
0x00,0x06,0x00,0x03,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x03,0x00,0x00,0x00,
0x00,0x06,0x00,0x07,0x03,0x00,0x77,0x46,0x74,0x24,0x80,0x06,0x04,0x00,0x00,0x00,
0x00,0x1C,0x00,0x06,0x00,0x00,0x55,0x45,0x54,0x57,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x1C,0x00,0x0E,0x00,0x00,0x45,0x45,0x74,0x57,0x80,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1C,0x00,0x00,0x55,0x45,0x44,0x74,0x80,0xF0,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x00,0x00,0x77,0x76,0x47,0x54,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
}; //128X32

int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	LCD_GPIO_Init();
  LCD_Init();
  delay_ms(20);
  LCD_Clear();
  delay_ms(10);
	
	while(1)
	{
			 	lcd_wstr(1,1,"PB18061426");
				lcd_wstr(2,1,"赵泊尧");
		LCD_Display_Words(1,1,"PB18061426");
		LCD_Display_Words(2,1,"赵泊尧");
		delay_ms(5000);		
		LCD_Clear();
		LCD_Display_Picture(ImageData);
		delay_ms(5000);
		LCD_Clear();
		
	}
}
	*/
	/*TIM3两个周期********************************************************************************/
	/*
	delay_init(168);	//???????
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//??????????? 2
	LED_Init();
	DIP_Init();
	TIM3_Init(83, 49999);
	while(1)
	{
		
	}
	*/
	/*DIP按键****************************************************************************************/
	/*
	LED_Init();		       //初始化LED端口
	delay_init(168);     //初始化延时函数
	DIP_Init();
	while(1)
	{
		//LED0 = 1;
		//delay_ms(500);
		//LED0 = 0;
		//delay_ms(500);
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
	*/
}


