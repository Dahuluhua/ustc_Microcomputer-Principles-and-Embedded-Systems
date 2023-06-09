#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
void KEY_Init(void);	 				    
#endif

