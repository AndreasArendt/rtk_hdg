#include "esp_log.h"
#include <stdio.h>

#include "ubx_parse.h"
#include "wifi.h"
#include "uart.h"
#include "json_serialize.h"

u_ubx_msg_t ubx_msg = {0};

void handle_ubx_message(e_ubx_msg_type_t type, void *msg)
{
    cJSON *json = NULL;
    if (type == MSG_TYPE_NAV_PVT)
    {
        json = pvt_to_json((s_ubx_msg_nav_pvt_t *)msg);
    }
    else if (type == MSG_TYPE_NAV_RELPOSNED)
    {
        json = relposned_to_json((s_ubx_msg_nav_relposned_t *)msg);
    }
    if (json)
    {
        char *str = cJSON_PrintUnformatted(json);
        printf("%s\n", str);
        free(str);
        cJSON_Delete(json);
    }
}

void app_main(void)
{
    uint8_t data[BUF_SIZE];

    init_uart();
    // init_wifi();

    while (1)
    {
        int len = uart_read(data);
        for (int i = 0; i < len; i++)
        {
            e_ubx_msg_type_t msg_type = ubx_parse(data[i], &ubx_msg);
            if (msg_type != MSG_TYPE_UNKNOWN)
            {
                handle_ubx_message(msg_type, &ubx_msg);
            }
        }
    }
}