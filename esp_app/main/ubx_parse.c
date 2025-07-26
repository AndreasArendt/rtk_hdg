#include "ubx_parse.h"
#include <stdio.h>

static e_ubx_msg_type_t mapping_message_type(e_ubx_header *header)
{
    if (header->msg_class == 0x01 && header->msg_id == 0x07)
    {
        return MSG_TYPE_NAV_PVT;
    }

    return MSG_TYPE_UNKNOWN;
}

e_ubx_msg_type_t ubx_parse(uint8_t byte, u_ubx_msg_t *ubx_msg)
{
    e_ubx_msg_type_t retval = MSG_TYPE_UNKNOWN;
    static e_parse_state_t parse_state = PARSE_STATE_SYNC_1;
    static e_ubx_header ubx_header = {0};
    static uint8_t paylout_cnt = 0;

    switch (parse_state)
    {
    case PARSE_STATE_SYNC_1:
        if (byte == 0xB5)
            parse_state = PARSE_STATE_SYNC_2;
        break;

    case PARSE_STATE_SYNC_2:        
        if (byte == 0x62)
            parse_state = PARSE_STATE_CLASS;
        else
            parse_state = PARSE_STATE_SYNC_1;
        break;

    case PARSE_STATE_CLASS:
        ubx_header.msg_class = byte;
        parse_state = PARSE_STATE_MSG_ID;
        // printf("msg_class: %02X\n", ubx_header.msg_class);
        break;

    case PARSE_STATE_MSG_ID:
        ubx_header.msg_id = byte;
        parse_state = PARSE_STATE_LENGTH_1;
        // printf("msg_id: %02X\n", ubx_header.msg_id);
        break;

    case PARSE_STATE_LENGTH_1:
        ubx_header.msg_length = 0;
        ubx_header.msg_length |= byte;
        parse_state = PARSE_STATE_LENGTH_2;        
        break;

    case PARSE_STATE_LENGTH_2:
        ubx_header.msg_length |= (byte << 8);
        parse_state = PARSE_STATE_PAYLOAD;
        paylout_cnt = 0;

        // printf("length: %02X\n", ubx_header.msg_length);
        break;

    case PARSE_STATE_PAYLOAD:
        // printf("%02X ", byte);

        if (paylout_cnt < UBX_RAW_DATA_BUFFER - 1)
        {
            ubx_msg->raw_data[paylout_cnt] = byte;
            ++paylout_cnt;
        }
        else // error - restart parsing
        {        
            parse_state = PARSE_STATE_SYNC_1;
            break;
        }

        if (paylout_cnt == ubx_header.msg_length)        
        {            
            parse_state = PARSE_STATE_CRC_1;            
        }
        
        break;

    case PARSE_STATE_CRC_1:
        // printf("crc1 %02X ", byte);
        parse_state = PARSE_STATE_CRC_2;
        break;

    case PARSE_STATE_CRC_2:
        // printf("crc2 %02X ", byte);

        parse_state = PARSE_STATE_SYNC_1;
        retval = mapping_message_type(&ubx_header);
        break;

    default:
        parse_state = PARSE_STATE_SYNC_1;
        break;
    }

    return retval;
}