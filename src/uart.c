#include "uart.h"

static uint16_t compute_bd(uint32_t periph_clk, uint32_t baud_rate);
static void uart_init_rcc(void);
static void uart_init_gpio_modes(void);
static void uart_set_baudrates(uint16_t bd);
static void uart_dma_enable(void);
static void uart_rt_enable(void);
static void uart_dma_init(void);

static void uart_init_gpio_modes(void){

    GPIOA -> MODER |= GPIO_MODER_MODER9_1;
    GPIOA -> MODER &=~GPIO_MODER_MODER9_0;

    GPIOA -> MODER |= GPIO_MODER_MODER10_1;
    GPIOA -> MODER &=~GPIO_MODER_MODER10_0;

    GPIOA -> MODER |= GPIO_MODER_MODER11_1;
    GPIOA -> MODER &=~GPIO_MODER_MODER11_0;

    GPIOA -> MODER |= GPIO_MODER_MODER12_1;
    GPIOA -> MODER &=~GPIO_MODER_MODER12_0;

    GPIOA -> AFR[1] |= (GPIO_AF_USART1 << 4);
    GPIOA -> AFR[1] |= (GPIO_AF_USART1 << 8);

    GPIOA -> AFR[1] |= (GPIO_AF_USART6 << 12);
    GPIOA -> AFR[1] |= (GPIO_AF_USART6 << 16);
}

static void uart_set_baudrates(uint16_t bd){
    USART1 -> BRR = bd;
    USART6 -> BRR = bd;
}

void uart_init_rcc(void){

    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC -> APB2ENR |= RCC_APB2ENR_USART6EN;
}

void uart_init_periph(void){
    USART_DeInit(USART1);
    USART_DeInit(USART6);

    uart_init_rcc();
    uart_init_gpio_modes();

    uint16_t bd = compute_bd(HSI_VALUE, RX_SPEED);

    uart_set_baudrates(bd);
    uart_rt_enable();
    uart_dma_enable();
}

static uint16_t compute_bd(uint32_t periph_clk, uint32_t baud_rate){
    return ((periph_clk + (baud_rate/2U))/baud_rate);
}

static void uart_rt_enable(void){
    USART1 -> CR1 |= USART_CR1_TE;
    USART1 -> CR1 |= USART_CR1_RE;

    USART6 -> CR1 |= USART_CR1_TE;
    USART6 -> CR1 |= USART_CR1_RE;
}

static void uart_dma_enable(void){
    USART1 -> CR3 |= USART_CR3_DMAR;
    USART1 -> CR3 |= USART_CR3_DMAT;

    USART6 -> CR3 |= USART_CR3_DMAR;
    USART6 -> CR3 |= USART_CR3_DMAT;
}

static void uart_dma_init(void){
    DMA_DeInit(DMA2_Stream7);
    DMA_DeInit(DMA2_Stream2);

    RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    DMA2_Stream2 -> CR &=~DMA_SxCR_EN;
    while(DMA2_Stream2 -> CR & DMA_SxCR_EN){}

    DMA2_Stream7 -> CR &=~DMA_SxCR_EN;
    while(DMA2_Stream7 -> CR & DMA_SxCR_EN){}

    DMA2 -> HIFCR |= (DMA_HIFCR_CFEIF7 | DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CTEIF7 | DMA_HIFCR_CHTIF7 | DMA_HIFCR_CTCIF7);
    DMA2 -> LIFCR |= (DMA_LIFCR_CFEIF2 | DMA_LIFCR_CDMEIF2 | DMA_LIFCR_CTEIF2 | DMA_LIFCR_CHTIF2 | DMA_LIFCR_CTCIF2);

    
}