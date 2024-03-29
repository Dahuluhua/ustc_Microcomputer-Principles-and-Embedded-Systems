#include "12864.h"
#include "delay.h"
 
void LCD_GPIO_Init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	CS = 1;	
  SID = 1;
  SCLK = 1;
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

void Lcd_WriteCmd(u8 Cmd)
{
     delay_ms(1);    
     SendByte(WRITE_CMD);            //11111,RW(0),RS(0),0   
     SendByte(0xf0&Cmd);      
     SendByte(Cmd<<4);   
}

void Lcd_WriteData(u8 Dat)
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



/*
#include "12864.h"
#include "delay.h"

// GPIO_InitTypeDef GPIO_InitStructure;
void Delay(__IO uint32_t nCount)
{
   for(; nCount != 0; nCount--);
}
void pcb_GPIO_Init(void)
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
 	
   
 }

void pcb_Init(void)
 {
//   pcb_RCC_Config();
  pcb_GPIO_Init();
//  delay_init(72);
  CS_1;
  lcd_init();
  
 }

void send_dat(unsigned char dat)
{
    unsigned char i;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    for(i=0;i<8;i++)
    {
		if((dat&0x80)==0x80) SID_1;
		if((dat&0x80)==0x00) SID_0;
        CLK_0;
		Delay(35);
        CLK_1;
		dat<<=1;
    }
}


unsigned char get_byte()
{
     unsigned char i,temp1=0,temp2=0;
	 //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     
     for(i=0;i<8;i++)   
     {   
           temp1=temp1<<1;   
           CLK_0;  
		   Delay(25); 
           CLK_1;  
		   Delay(20);              
           CLK_0;   
           if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_3)) temp1++;   
     }   
     for(i=0;i<8;i++)   
     {   
           temp2=temp2<<1;   
           CLK_0;  
		   Delay(25);  
           CLK_1; 
		   Delay(25);   
           CLK_0;   
           if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_3))  temp2++;   
     }   
	 //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     return ((0xf0&temp1)+(0x0f&temp2));   
}

void check_busy()
{
    do
    {
        send_dat(0xfc);
    }
    while((get_byte()&0x8000)==0x8000);
}

void send_cmd(unsigned char cmd)
{
    check_busy();
    send_dat(0xf8);    //
    send_dat(cmd&0xf0); //
    send_dat((cmd&0x0f)<<4); //
}

void write_char(unsigned char dat)
{
    check_busy();
    send_dat(0xfa);//rw=0;rs=1
    send_dat(dat&0xf0);
    send_dat((dat&0x0f)<<4);
}

void lcd_clear()        //清除显示
{
    send_cmd(0x01);
}


void lcd_pos(unsigned char y_add , unsigned char x_add)
{
    switch(y_add)
    {
        case 1:
        send_cmd(0X80|x_add);break;
        case 2:
        send_cmd(0X90|x_add);break;
        case 3:
        send_cmd(0X88|x_add);break;
        case 4:
        send_cmd(0X98|x_add);break;
        default:break;
    }    
}


void lcd_wstr(unsigned char y_add , unsigned char x_add , unsigned char *str)    //
{
    unsigned char i;
    lcd_pos(y_add , x_add);
    for(i=0;str[i]!='\0';i++)
    {
        write_char(str[i]);  
    }

}

void lcd_wstr2(unsigned char y_add , unsigned char x_add , unsigned char *str)    //
{
    unsigned char i;
    lcd_pos(y_add , x_add);
    for(i=0;str[i]!='\0';i++)
    {
        write_char(0x30+str[i]);  
    }

}




void write_figer(unsigned char y_add , unsigned char x_add , unsigned int figer)//在任何位置写数字
{
    unsigned char d[5],i,j;
    lcd_pos(y_add , x_add);
    d[4]=figer%10;
    d[3]=figer%100/10;
    d[2]=figer%1000/100;
    d[1]=figer%10000/1000;
    d[0]=figer/10000;
    for(i=0;i<5;i++)
    {
        if(d[i]!=0)
					break;
    }

    if(i==5)
			i--;

    if(i==4)
			send_dat(0x30);//数据装完，准备发送

    for(j=i;j<5;j++)
    {
       send_dat(d[j]+0x30);//取得的数字加上0x30也即得到该数字的ASCII码，再将该数字发送去显示
    }
 
}

void lcd_init()     //
{  

    Delay(0xfff);
    send_cmd(0x30);
    send_cmd(0x0C);//0000,1100 整体显示，游标off，游标位置off
    send_cmd(0x01);//0000,0001 清DDRAM
    send_cmd(0x02);//0000,0010 DDRAM地址归位
    send_cmd(0x80);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器A
}


******************* (C) COPYRIGHT 2011 奋斗STM32 *****END OF FILE****
*/
