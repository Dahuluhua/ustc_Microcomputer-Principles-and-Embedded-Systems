// GPIO_InitTypeDef GPIO_InitStructure;
void Delay(__IO uint32_t nCount)
{
   for(; nCount != 0; nCount--);
}
void pcb_GPIO_Init(void)
 { 
	 
	   GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOF, ENABLE);//��1?��GPIOF����?��

  //GPIOF9,F103?��??������??
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??������?3??�꨺?
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//��?������?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��?��-
   GPIO_Init(GPIOF, &GPIO_InitStructure);
	 
	 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//??������?3??�꨺?
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//��?������?3?
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//��?��-
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

void lcd_clear()        //??3y??��?
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




void write_figer(unsigned char y_add , unsigned char x_add , unsigned int figer)//?����?o?????D�䨺y��?
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
			send_dat(0x30);//��y?Y���㨪����?��?��?����?��

    for(j=i;j<5;j++)
    {
       send_dat(d[j]+0x30);//��?��?��?��y��??����?0x30��2?���?��???��y��?��?ASCII??��??��????��y��?����?������??��?
    }
 
}

void lcd_init()     //
{  

    Delay(0xfff);
    send_cmd(0x30);
    send_cmd(0x0C);//0000,1100 ??��???��?��?��?����off��?��?����????off
    send_cmd(0x01);//0000,0001 ??DDRAM
    send_cmd(0x02);//0000,0010 DDRAM��??��1��??
    send_cmd(0x80);//1000,0000 ����?��DDRAM 7??��??��000��?0000��?��??��??��y?��A
}


/******************* (C) COPYRIGHT 2011 ����?��STM32 *****END OF FILE****/