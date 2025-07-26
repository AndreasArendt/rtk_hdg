#include "driver/uart.h"
#include "esp_log.h"
#include <stdio.h>
#include "driver/gpio.h"

#include "ubx_parse.h"

#define UART_PORT_NUM UART_NUM_1
#define UART_RX_PIN GPIO_NUM_16
#define UART_TX_PIN GPIO_NUM_17 // Optional
#define BUF_SIZE 1024

u_ubx_msg_t ubx_msg = {0};


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
            for (int i = 0; i < len; i++)
            { 
                e_ubx_msg_type_t msg_type = ubx_parse(data[i], &ubx_msg);

                if(msg_type == MSG_TYPE_NAV_PVT)
                {
                    printf("numSV: %d, fixType %d\n", ubx_msg.msg_nav_pvt.numSV, ubx_msg.msg_nav_pvt.fixType);
                }
            }            
        }
    }
}