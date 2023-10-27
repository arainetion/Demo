#include "led.h"

void LedInit(void)
{
    GPIO_InitTypeDef LedStruct = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    LedStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    LedStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    LedStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOE, &LedStruct);

    GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
}