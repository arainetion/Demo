//
// Created by 10525 on 2023/9/2.
//

#include "usart.h"

/**
 * @brief 串口1初始化
 * @param baud 波特率
 */

u8 transferData = 0;

void UsartInit(u32 baud)
{
    GPIO_InitTypeDef gpioInit = {0};
    USART_InitTypeDef usartInitStruct = {0};
    NVIC_InitTypeDef nvic = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

    gpioInit.GPIO_Pin = GPIO_Pin_10;
    gpioInit.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioInit);

    gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
    gpioInit.GPIO_Pin = GPIO_Pin_9;
    gpioInit.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioInit);
		GPIO_SetBits(GPIOE,GPIO_Pin_6);//空闲为高电平

    usartInitStruct.USART_BaudRate = baud; //波特率
    usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
    usartInitStruct.USART_Parity = USART_Parity_No; //禁止校验
    usartInitStruct.USART_StopBits = USART_StopBits_1; //停止位1位
    usartInitStruct.USART_WordLength = USART_WordLength_8b; //数据位8位
    usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不使用硬件控制流
    USART_Init(USART1, &usartInitStruct);

    //配置中断，
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //接收缓冲区非空中断使能
    //配置NVIC通知内核执行中断服务函数
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannel = USART1_IRQn;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_Init(&nvic);
    USART_Cmd(USART1, ENABLE);
}

void Usart1SendByte(USART_TypeDef *USARTx, u8 data)
{
    //判断发送寄存器是否为空
    if (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == SET)
    {
        USART_SendData(USARTx, data);
    } else
    {
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //等发送完毕
        USART_SendData(USARTx, data);
    }
}

u8 Usart1RecvByte(void)
{
    //判断是否接收到数据
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART1);
}

void USART1_IRQHandler()
{
    if (!USART_GetITStatus(USART1, USART_IT_RXNE))
        return;
    transferData = USART_ReceiveData(USART1);
    USART3->DR = transferData; //转发给串口三
    //清中断
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

//keil中实现printf输出串口
int fputc(int ch, FILE *stream)
{
    while (!USART_GetFlagStatus(USART1, USART_FLAG_TC));
    USART_SendData(USART1, (u16)ch);
    return ch;
}

void Usart1SendStr(USART_TypeDef *USARTx, char *str)
{
    while (*str != '\0')
    {
        Usart1SendByte(USARTx, *str);
        str++;
    }
}

void Usart1SendBuff(USART_TypeDef *USARTx, char *str, int len)
{
    for (int i = 0; i < len; ++i)
    {
        Usart1SendByte(USART3,str[i]);
    }
}
