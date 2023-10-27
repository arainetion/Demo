/*
 * ************************************************
 * 
 * STM32 blink demo
 * 
 * CPU:     STM32F103ZE
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "led.h"
#include "usart.h"

void delay(int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}

int main()
{
    LedInit();
    UsartInit(115200);

    while (1)
    {
        LED1TOGGLE;
        LED2TOGGLE;
        LED3TOGGLE;
        LED4TOGGLE;
        printf("hello,world\r\n");
        delay(5000);
    }
}
