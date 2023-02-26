#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

#define RX_SPEED    115200

void uart_init_periph(char *u1_dst, uint16_t u1_len, char *u6_dst, uint16_t u6_len);
void uart_write_dma(DMA_Stream_TypeDef *dtstr, uint32_t memptr, uint16_t dtlngth);

#endif