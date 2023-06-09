#ifndef __lcd12864_H_
#define __lcd12864_H_

#include "sys.h"

static u8 LCD_addr[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		
};

#define WRITE_CMD	0xF8
#define WRITE_DAT	0xFA

#define SID PFout(15)
#define SCLK PFout(14)
#define CS PGout(1)  

void LCD_GPIO_Init(void);
void SendByte(u8 byte);
void Lcd_WriteCmd(u8 Cmd);
void Lcd_WriteData(u8 Dat);
void LCD_Init(void);
void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str);
void LCD_Display_Picture(uint8_t *img);
void LCD_Clear(void);

#endif

/*
#ifndef __12864_H
#define __12864_H

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define CLK_1 GPIO_SetBits(GPIOF, GPIO_Pin_14);  
#define CLK_0 GPIO_ResetBits(GPIOF, GPIO_Pin_14); 

#define SID_1 GPIO_SetBits(GPIOF, GPIO_Pin_15);  
#define SID_0 GPIO_ResetBits(GPIOF, GPIO_Pin_15); 

#define CS_1 GPIO_SetBits(GPIOG, GPIO_Pin_1);  
#define CS_0 GPIO_ResetBits(GPIOG, GPIO_Pin_1);


void Delay(__IO uint32_t nCount);
unsigned char get_byte(void);
void check_busy(void);
void send_cmd(unsigned char cmd);
void write_char(unsigned char dat);
void lcd_clear(void);        //清除显示
void lcd_pos(unsigned char y_add , unsigned char x_add);
void lcd_wstr(unsigned char y_add , unsigned char x_add , unsigned char *str) ;
void write_figer(unsigned char y_add , unsigned char x_add , unsigned int figer);//在任何位置写数字
void lcd_init(void);     //
void Delay(__IO uint32_t nCount);
void pcb_Init(void);
void pcb_GPIO_Init(void);
void lcd_wstr2(unsigned char y_add , unsigned char x_add , unsigned char *str) ;
 
#endif 
*/
