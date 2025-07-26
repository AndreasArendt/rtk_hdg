#include "driver/uart.h"
#include "esp_log.h"
#include <stdio.h>
#include "driver/gpio.h"

#define UART_PORT_NUM UART_NUM_1
#define UART_RX_PIN GPIO_NUM_16
#define UART_TX_PIN GPIO_NUM_17 // Optional
#define BUF_SIZE 1024

void app_main(void)
{
    uart_config_t uart_config = {
        .baud_rate = 38400,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

    uart_driver_install(UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_PORT_NUM, &uart_config);
    uart_set_pin(UART_PORT_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uint8_t data[BUF_SIZE];

    while (1)
    {
        int len = uart_read_bytes(UART_PORT_NUM, data, BUF_SIZE, pdMS_TO_TICKS(100));
        if (len > 0)
        {
            printf("Received %d bytes: ", len);
            for (int i = 0; i < len; i++)
            {
                printf("%02X ", data[i]);
            }
            printf("\n");
        }
    }
}

typedef enum
{

} e_parse_state_t;

void
parse(uint8_t byte)
{
}