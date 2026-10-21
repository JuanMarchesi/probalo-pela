#include "usart.h"
#include "stm32f103xb.h"
#include "clk_maximizer.h"

int main (void){

    clock_72MHz();
    usart_init(USART1, 9600);
    usart_send_char(USART1, 'k');

}