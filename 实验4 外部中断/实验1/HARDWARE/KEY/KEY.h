#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
void KEY_Init(void);	 				    
#endif

