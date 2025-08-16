#include "json_serialize.h"

cJSON* relposned_to_json(const s_ubx_msg_nav_relposned_t* msg)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "version", msg->version);
    cJSON_AddNumberToObject(root, "reserved0", msg->reserved0);
    cJSON_AddNumberToObject(root, "refStationId", msg->refStationId);
    cJSON_AddNumberToObject(root, "iTOW", msg->iTOW);
    cJSON_AddNumberToObject(root, "relPosN", msg->relPosN);
    cJSON_AddNumberToObject(root, "relPosE", msg->relPosE);
    cJSON_AddNumberToObject(root, "relPosD", msg->relPosD);
    cJSON_AddNumberToObject(root, "relPosLength", msg->relPosLength);
    cJSON_AddNumberToObject(root, "relPosHeading", msg->relPosHeading);

    // reserved1 as array
    cJSON *res1 = cJSON_CreateArray();
    for (int i = 0; i < 4; i++)
        cJSON_AddItemToArray(res1, cJSON_CreateNumber(msg->reserved1[i]));
    cJSON_AddItemToObject(root, "reserved1", res1);

    cJSON_AddNumberToObject(root, "relPosHPN", msg->relPosHPN);
    cJSON_AddNumberToObject(root, "relPosHPE", msg->relPosHPE);
    cJSON_AddNumberToObject(root, "relPosHPD", msg->relPosHPD);
    cJSON_AddNumberToObject(root, "relPosHPLength", msg->relPosHPLength);

    cJSON_AddNumberToObject(root, "accN", msg->accN);
    cJSON_AddNumberToObject(root, "accE", msg->accE);
    cJSON_AddNumberToObject(root, "accD", msg->accD);
    cJSON_AddNumberToObject(root, "accLength", msg->accLength);
    cJSON_AddNumberToObject(root, "accHeading", msg->accHeading);

    // reserved2 as array
    cJSON *res2 = cJSON_CreateArray();
    for (int i = 0; i < 4; i++)
        cJSON_AddItemToArray(res2, cJSON_CreateNumber(msg->reserved2[i]));
    cJSON_AddItemToObject(root, "reserved2", res2);

    cJSON_AddNumberToObject(root, "flags", msg->flags);

    return root;
}

cJSON* pvt_to_json(const s_ubx_msg_nav_pvt_t* msg)
{
    cJSON *root = cJSON_CreateObject();

    cJSON_AddNumberToObject(root, "iTOW", msg->iTOW);
    cJSON_AddNumberToObject(root, "year", msg->year);
    cJSON_AddNumberToObject(root, "month", msg->month);
    cJSON_AddNumberToObject(root, "day", msg->day);
    cJSON_AddNumberToObject(root, "hour", msg->hour);
    cJSON_AddNumberToObject(root, "min", msg->min);
    cJSON_AddNumberToObject(root, "sec", msg->sec);
    cJSON_AddNumberToObject(root, "valid", msg->valid);
    cJSON_AddNumberToObject(root, "tAcc", msg->tAcc);
    cJSON_AddNumberToObject(root, "nano", msg->nano);
    cJSON_AddNumberToObject(root, "fixType", msg->fixType);
    cJSON_AddNumberToObject(root, "flags", msg->flags);
    cJSON_AddNumberToObject(root, "flags2", msg->flags2);
    cJSON_AddNumberToObject(root, "numSV", msg->numSV);
    cJSON_AddNumberToObject(root, "lon", msg->lon);
    cJSON_AddNumberToObject(root, "lat", msg->lat);
    cJSON_AddNumberToObject(root, "height", msg->height);
    cJSON_AddNumberToObject(root, "hMSL", msg->hMSL);
    cJSON_AddNumberToObject(root, "hAcc", msg->hAcc);
    cJSON_AddNumberToObject(root, "vAcc", msg->vAcc);
    cJSON_AddNumberToObject(root, "velN", msg->velN);
    cJSON_AddNumberToObject(root, "velE", msg->velE);
    cJSON_AddNumberToObject(root, "velD", msg->velD);
    cJSON_AddNumberToObject(root, "gSpeed", msg->gSpeed);
    cJSON_AddNumberToObject(root, "headMot", msg->headMot);
    cJSON_AddNumberToObject(root, "sAcc", msg->sAcc);
    cJSON_AddNumberToObject(root, "headAcc", msg->headAcc);
    cJSON_AddNumberToObject(root, "pDOP", msg->pDOP);
    cJSON_AddNumberToObject(root, "flags3", msg->flags3);
    cJSON_AddNumberToObject(root, "headVeh", msg->headVeh);
    cJSON_AddNumberToObject(root, "magDec", msg->magDec);
    cJSON_AddNumberToObject(root, "magAcc", msg->magAcc);

    return root;
}