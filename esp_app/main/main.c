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
    //init_wifi();

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
                    char msg[128];
                    snprintf(msg, sizeof(msg), "SVs: %d, Fix: %d, Lat: %.2f, Lon: %.2f, Alt %.2f\n",
                             ubx_msg.msg_nav_pvt.numSV,
                             ubx_msg.msg_nav_pvt.fixType,
                             ubx_msg.msg_nav_pvt.lat * 1.0e-7,
                             ubx_msg.msg_nav_pvt.lon * 1.0e-7,
                             ubx_msg.msg_nav_pvt.hMSL * 1.0e-3);
                    //wifi_send(&msg[0]);
                    printf(&msg[0]);
                }
                else if (msg_type == MSG_TYPE_NAV_RELPOSNED)
                {
                    char msg[128];
                    snprintf(msg, sizeof(msg), "relposN: %ld, relposE: %ld, relposD: %ld, acc_hdg %ld, heading %.2f, flags %ld\n",
                             ubx_msg.msg_nav_relposned.relPosN,
                             ubx_msg.msg_nav_relposned.relPosE,
                             ubx_msg.msg_nav_relposned.relPosD,
                             ubx_msg.msg_nav_relposned.accHeading,
                             ubx_msg.msg_nav_relposned.relPosHeading * 1.0e-5,
                             ubx_msg.msg_nav_relposned.flags);
                    //wifi_send(&msg[0]);
                    printf(&msg[0]);
                }
            }
        }
    }
}