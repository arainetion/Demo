#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"

#define LED1TOGGLE (GPIOE->ODR ^= (1 << 2))
#define LED2TOGGLE (GPIOE->ODR ^= (1 << 3))
#define LED3TOGGLE (GPIOE->ODR ^= (1 << 4))
#define LED4TOGGLE (GPIOE->ODR ^= (1 << 5))
#define LED1ON  GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define LED1OFF GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define LED2ON  GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define LED2OFF GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define LED3ON  GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define LED3OFF GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define LED4ON  GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define LED4OFF GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define CONSTANT 1
#define LEVEL1 100
#define LEVEL2 500

void LedInit();

#endif