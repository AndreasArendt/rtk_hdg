#include "esp_log.h"
#include <stdio.h>

#include "ubx_parse.h"
#include "wifi.h"
#include "uart.h"

u_ubx_msg_t ubx_msg = {0};

void app_main(void)
{
    uint8_t data[BUF_SIZE];

    init_uart();
    init_wifi();

    while (1)
    {
        int len = uart_read(&data[0]);
        if (len > 0)
        {
            for (int i = 0; i < len; i++)
            {
                e_ubx_msg_type_t msg_type = ubx_parse(data[i], &ubx_msg);

                if (msg_type == MSG_TYPE_NAV_PVT)
                {
                    char msg[64];
                    snprintf(msg, sizeof(msg), "SVs: %d, Fix: %d\n", ubx_msg.msg_nav_pvt.numSV, ubx_msg.msg_nav_pvt.fixType);
                    wifi_send(&msg[0]);
                }
            }
        }
    }
}