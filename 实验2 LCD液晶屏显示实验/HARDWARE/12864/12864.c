#include "12864.h"
#include "delay.h"

void LCD_GPIO_Init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
   GPIO_Init(GPIOF, &GPIO_InitStructure);
	 
	 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);		
	CS=1;	
  SID=1;
  SCLK=1;
}
void SendByte(u8 byte)
{
     u8 i; 
	  for(i = 0;i < 8;i++)
    {
			if((byte << i) & 0x80)  //0x80(1000 0000)  			
{

				SID = 1;           
}
			else
			{
				SID = 0;        
			}
		
			SCLK = 0;  
			delay_us(5); 
			SCLK = 1;    
		}   
}
void Lcd_WriteCmd(u8 Cmd )
{
     delay_ms(1);    
     SendByte(WRITE_CMD);            //11111,RW(0),RS(0),0   
     SendByte(0xf0&Cmd);      
     SendByte(Cmd<<4);   
}


void Lcd_WriteData(u8 Dat )
{
     delay_ms(1);     
     SendByte(WRITE_DAT);           
     SendByte(0xf0&Dat);     
     SendByte(Dat<<4);  
}

void LCD_Init(void)
{ 
	delay_ms(50);   	
	 Lcd_WriteCmd(0x30);       

	delay_ms(1);
	 Lcd_WriteCmd(0x30);      

	delay_ms(1);	
	Lcd_WriteCmd(0x0c);   
  
	delay_ms(1);	
	Lcd_WriteCmd(0x01);     
   
	delay_ms(30);	
	 Lcd_WriteCmd(0x06);      
}
void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str)
{ 
	Lcd_WriteCmd(LCD_addr[x][y]);
	while(*str>0)
    { 
      Lcd_WriteData(*str);    
      str++;     
    }
}

void LCD_Display_Picture(uint8_t *img)
{
		uint8_t x,y,i;
		Lcd_WriteCmd(0x34);		
		Lcd_WriteCmd(0x34);		
		for(i = 0; i < 2; i++)  
		{
			for(y=0;y<32;y++)   
			{  
				for(x=0;x<8;x++)   
				{
					Lcd_WriteCmd(0x80 + y);		
					Lcd_WriteCmd(0x80 + x+i*0x08);		

					Lcd_WriteData(*img ++);		
  
					Lcd_WriteData(*img ++);		
				}
			}
		}
		Lcd_WriteCmd(0x36);		
		Lcd_WriteCmd(0x30);       
}	

void LCD_Clear(void)
{
		Lcd_WriteCmd(0x01);			
		delay_ms(2);				
}
