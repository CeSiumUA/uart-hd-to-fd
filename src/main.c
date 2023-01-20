#include "main.h"
#include "stm32f4xx.h"



static void init_irq(void){
    __disable_irq();
    __enable_irq();
}

int main(void){
    
    RCC_DeInit();
    GPIO_DeInit(GPIOA);
    
    init_irq();

    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    uart_init_periph();

    while(1){
        
    }
}

// USART6 RX
void DMA2_Stream1_IRQHandler(void){

}

// USART1 RX
void DMA2_Stream2_IRQHandler(void){
    
}

// USART6 TX
void DMA2_Stream6_IRQHandler(void){
    
}

// USART1 TX
void DMA2_Stream7_IRQHandler(void){
    
}

// USART2 RX
void DMA1_Stream5_IRQHandler(void){
    
}

// USART2 TX
void DMA1_Stream6_IRQHandler(void){
    
}