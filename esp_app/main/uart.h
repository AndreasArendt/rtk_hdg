#ifndef UART_H_
#define UART_H_

#include "driver/gpio.h"

#define BUF_SIZE 1024

int uart_read(uint8_t* buffer);
void init_uart();

#endif