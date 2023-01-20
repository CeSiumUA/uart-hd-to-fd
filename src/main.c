#include "main.h"
#include "stm32f4xx.h"

char u2_rx_buf[1];
char u1_rx_buf[1];
char u6_rx_buf[1];

static void init_irq(void){
    __disable_irq();
    __enable_irq();
}

int main(void){
    
    RCC_DeInit();
    GPIO_DeInit(GPIOA);
    
    init_irq();

    uart_init_periph(u1_rx_buf, sizeof(u1_rx_buf), u2_rx_buf, sizeof(u2_rx_buf), u6_rx_buf, sizeof(u6_rx_buf));

    while(1){
        
    }
}

// USART6 RX
void DMA2_Stream1_IRQHandler(void){
    if(!(DMA2 -> LISR & DMA_LISR_TCIF1)){
        return;
    }

    while(DMA1_Stream6 -> CR & DMA_SxCR_EN){}

    DMA1_Stream6 -> M0AR = (uint32_t)u6_rx_buf;

    DMA1_Stream6 -> NDTR = (uint16_t)sizeof(u6_rx_buf);

    DMA1_Stream6 -> CR |= DMA_SxCR_EN;

    DMA2 -> LIFCR |= (DMA_LIFCR_CFEIF1 | DMA_LIFCR_CDMEIF1 | DMA_LIFCR_CTEIF1 | DMA_LIFCR_CHTIF1 | DMA_LIFCR_CTCIF1);
}

// USART1 RX
void DMA2_Stream2_IRQHandler(void){
    
}

// USART6 TX
void DMA2_Stream6_IRQHandler(void){
    
}

// USART1 TX
void DMA2_Stream7_IRQHandler(void){
    DMA2 -> HIFCR |= (DMA_HIFCR_CFEIF7 | DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CTEIF7 | DMA_HIFCR_CHTIF7 | DMA_HIFCR_CTCIF7);
}

// USART2 RX
void DMA1_Stream5_IRQHandler(void){
    if(!(DMA1 -> HISR & DMA_HISR_TCIF5)){
        return;
    }

    while(DMA2_Stream7 -> CR & DMA_SxCR_EN){}
    
    DMA2_Stream7 -> M0AR = (uint32_t)u2_rx_buf;

    DMA2_Stream7 -> NDTR = (uint16_t)sizeof(u2_rx_buf);

    DMA2_Stream7 -> CR |= DMA_SxCR_EN;

    DMA1 -> HIFCR |= (DMA_HIFCR_CFEIF5 | DMA_HIFCR_CDMEIF5 | DMA_HIFCR_CTEIF5 | DMA_HIFCR_CHTIF5 | DMA_HIFCR_CTCIF5);
}

// USART2 TX
void DMA1_Stream6_IRQHandler(void){
    DMA1 -> HIFCR |= (DMA_HIFCR_CFEIF6 | DMA_HIFCR_CDMEIF6 | DMA_HIFCR_CTEIF6 | DMA_HIFCR_CHTIF6 | DMA_HIFCR_CTCIF6);
}