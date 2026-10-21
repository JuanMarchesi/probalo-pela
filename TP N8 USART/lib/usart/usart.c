#include "usart.h"

int mantissa;
int fraction; 
float valor;
int PCLK=0;
int PA9 = 9;
int PA10 = 10;
int PA2 = 3;
int PA3 = 4;
int PB10 = 5;
int PB11 = 6;

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){

    if (USARTx == USART1)
    {
        PCLK = 72000000;
        RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<(PA9 %8)*4 );
        GPIOA->CRH |=(0XB<<(PA9 %8)*4 );
        GPIOA->CRH&=~(0XF<<(PA10%8)*4);
        GPIOA->CRH |=(0XB<<(PA10%8)*4);
        valor =PCLK/(16*baudrate);
    }
        
    if (USARTx == USART2)
    {
        PCLK = 36000000;
        RCC -> APB1ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB1ENR |= RCC_APB2ENR_AFIOEN;
        RCC -> APB1ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<PA2*4);
        GPIOA->CRH |=(0XB<<PA2*4);
        GPIOA->CRH&=~(0XF<<PA3*4);
        GPIOA->CRH |=(0XB<<PA3*4);;
        valor =PCLK/(16*baudrate);
    }

    if (USARTx == USART3)
    {
        PCLK = 36000000;
        RCC -> APB1ENR |= RCC_APB2ENR_USART1EN;
        RCC -> APB1ENR |= RCC_APB2ENR_AFIOEN;
        RCC -> APB1ENR |= RCC_APB2ENR_IOPAEN;
        GPIOA->CRH&=~(0XF<<PB10*4);
        GPIOA->CRH |=(0XB<<PB10*4);
        GPIOA->CRH&=~(0XF<<PB11*4);
        GPIOA->CRH |=(0XB<<PB11*4);;
        valor =PCLK/(16*baudrate);
    }
        mantissa = valor;
        fraction = (valor-mantissa)*100;
        USARTx ->BRR = (mantissa << 4)| fraction;
        USARTx->CR1|=USART_CR1_UE;
        USARTx->CR1|=USART_CR1_TE;
        USARTx->CR1|=USART_CR1_RE;
}

void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    while(!(USARTx -> SR & USART_SR_TXE))
    USARTx -> DR = data;
}

void usart_send_string(USART_TypeDef* USARTx, char* texto ){
    
    while (*texto){
        usart_send_char(USARTx, *texto);
        texto++;
    }
}

uint8_t usart_receive_char(USART_TypeDef * USARTx) {
        while(!(USART1 -> SR & USART_SR_RXNE));
        return USART1->DR;
    }

