#ifndef JSON_SERIALIZE_H_
#define JSON_SERIALIZE_H_

#include "cJSON.h"
#include "ubx_messages.h"

cJSON* relposned_to_json(const s_ubx_msg_nav_relposned_t* msg);
cJSON* pvt_to_json(const s_ubx_msg_nav_pvt_t* msg);

#endif 