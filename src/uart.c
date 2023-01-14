#include "uart.h"

static uint16_t compute_bd(uint32_t periph_clk, uint32_t baud_rate);
static void uart_init_rcc(void);
static void uart_init_gpio_modes(void);
static void uart_set_baudrates(uint16_t bd);

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
    uart_init_periph();

    uint16_t bd = compute_bd(HSI_VALUE, RX_SPEED);

    uart_set_baudrates(bd);
}

static uint16_t compute_bd(uint32_t periph_clk, uint32_t baud_rate){
    return ((periph_clk + (baud_rate/2U))/baud_rate);
}