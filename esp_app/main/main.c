#include "driver/uart.h"
#include "esp_log.h"
#include <stdio.h>
#include "driver/gpio.h"

#include "ubx_parse.h"
#include "wifi_settings.h"

#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>         // for close()

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

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

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(1234),
        .sin_addr.s_addr = inet_addr("192.168.0.225")
    };

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

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
                    char msg[64];
                    snprintf(msg, sizeof(msg), "SVs: %d, Fix: %d\n", ubx_msg.msg_nav_pvt.numSV, ubx_msg.msg_nav_pvt.fixType);
                    send(sock, msg, strlen(msg), 0);

                    printf("numSV: %d, fixType %d\n", ubx_msg.msg_nav_pvt.numSV, ubx_msg.msg_nav_pvt.fixType);
                }
            }            
        }
    }
}