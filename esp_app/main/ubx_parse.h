#ifndef UBX_PARSE_H_
#define UBX_PARSE_H_

#include "ubx_messages.h"

typedef enum
{
    PARSE_STATE_SYNC_1,
    PARSE_STATE_SYNC_2,
    PARSE_STATE_CLASS,
    PARSE_STATE_MSG_ID,
    PARSE_STATE_LENGTH,
    PARSE_STATE_PAYLOAD,
    PARSE_STATE_CRC_1,
    PARSE_STATE_CRC_2
} e_parse_state_t;

typedef enum
{
    MSG_TYPE_UNKNOWN = 0,
    MSG_TYPE_NAV_PVT
} e_ubx_msg_type_t;

e_ubx_msg_type_t ubx_parse(uint8_t byte, u_ubx_msg_t* ubx_msg);

#endif