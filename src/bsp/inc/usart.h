//
// Created by 10525 on 2023/9/2.
//

#ifndef INC_824_LED_USART_H
#define INC_824_LED_USART_H

#include <stdio.h>
#include <string.h>
#include "stm32f10x.h"
#include "led.h"

void UsartInit(u32 baud);

void Usart1SendByte(USART_TypeDef *USARTx, u8 data);

u8 Usart1RecvByte(void);

void Usart1SendStr(USART_TypeDef *USARTx, char *str);

void Usart1SendBuff(USART_TypeDef *USARTx, char *str, int len);

#endif //INC_824_LED_USART_H
