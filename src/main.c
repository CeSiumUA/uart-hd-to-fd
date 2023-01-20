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


void DMA2_Stream1_IRQHandler(void){

}

void DMA2_Stream2_IRQHandler(void){
    
}

void DMA2_Stream6_IRQHandler(void){
    
}

void DMA2_Stream7_IRQHandler(void){
    
}

void DMA1_Stream5_IRQHandler(void){
    
}

void DMA1_Stream6_IRQHandler(void){
    
}