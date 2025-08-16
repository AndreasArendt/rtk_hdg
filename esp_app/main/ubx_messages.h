#ifndef UBX_MESSAGES_H_
#define UBX_MESSAGES_H_

#include <stdint.h>

#define UBX_RAW_DATA_BUFFER 128

typedef struct
{
    uint8_t msg_class;
    uint8_t msg_id;
    uint16_t msg_length;
} e_ubx_header;

#pragma pack(push, 1)
typedef struct
{
    uint32_t iTOW;    /**< GPS time of week of the
                       navigation epoch
                       in milliseconds. */
    uint16_t year;    /**< year (UTC); to obtain this and
                           the other time-related fields
                           in this structure as a Unix-based
                           UTC timestamp, see
                           uGnssDecUbxNavPvtGetTimeUtc(). */
    uint8_t month;    /**< month, range 1 to 12 (UTC). */
    uint8_t day;      /**< day of month, range 1 to 31 (UTC). */
    uint8_t hour;     /**< hour of day, range 0 to 23 (UTC). */
    uint8_t min;      /**< minute of hour, range 0 to 59 (UTC). */
    uint8_t sec;      /**< seconds of minute, range 0 to 60 (UTC). */
    uint8_t valid;    /**< validity flags, see
                           #uGnssDecUbxNavPvtValid_t. */
    uint32_t tAcc;    /**< time accuracy estimate in
                           nanoseconds. */
    int32_t nano;     /**< fractional seconds part of UTC
                           time in nanoseconds. */
    uint8_t fixType;  /**< the fix type achieved. */
    uint8_t flags;    /**< see #uGnssDecUbxNavPvtFlags_t. */
    uint8_t flags2;   /**< see #uGnssDecUbxNavPvtFlags2_t. */
    uint8_t numSV;    /**< the number of satellites used. */
    int32_t lon;      /**< longitude in degrees times 1e7. */
    int32_t lat;      /**< latitude in degrees times 1e7. */
    int32_t height;   /**< height above ellipsoid in mm. */
    int32_t hMSL;     /**< height above mean sea level in mm. */
    uint32_t hAcc;    /**< horizontal accuracy estimate in mm. */
    uint32_t vAcc;    /**< vertical accuracy estimate in mm. */
    int32_t velN;     /**< NED north velocity in mm/second. */
    int32_t velE;     /**< NED east velocity in mm/second. */
    int32_t velD;     /**< NED down velocity in mm/second. */
    int32_t gSpeed;   /**< 2D ground speed in mm/second. */
    int32_t headMot;  /**< 2D heading of motion in degrees times 1e5. */
    uint32_t sAcc;    /**< speed accuracy estimate in mm/second. */
    uint32_t headAcc; /**< heading accuracy estimate (motion and
                           vehicle) in degrees times 1e5. */
    uint16_t pDOP;    /**< position DOP times 100. */
    uint16_t flags3;  /**< see #uGnssDecUbxNavPvtFlags3_t. */
    int32_t headVeh;  /**< if the #U_GNSS_DEC_UBX_NAV_PVT_FLAGS_HEAD_VEH_VALID
                           bit of the flags field is set
                           then this is the 2D vehicle
                           heading in degrees times 1e5,
                           else it is set to the same
                           value as headMot. */
    int16_t magDec;   /**< if the #U_GNSS_DEC_UBX_NAV_PVT_VALID_MAG
                           bit of the valid field is set then this
                           is the magnetic declination in degrees
                           times 100; only supported on ADR 4.10
                           and later. */
    uint16_t magAcc;  /**< if the #U_GNSS_DEC_UBX_NAV_PVT_VALID_MAG
                           bit of the valid field is set then this
                           is the accuracy of the magnetic
                           declination in degrees times 100; only
                           supported on ADR 4.10 and later. */
} s_ubx_msg_nav_pvt_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
    uint8_t version;
    uint8_t reserved0;
    uint16_t refStationId;
    uint32_t iTOW;
    int32_t relPosN;
    int32_t relPosE;
    int32_t relPosD;
    int32_t relPosLength;
    int32_t relPosHeading;
    uint8_t reserved1[4];
    int8_t relPosHPN;
    int8_t relPosHPE;
    int8_t relPosHPD;
    int8_t relPosHPLength;
    uint32_t accN;
    uint32_t accE;
    uint32_t accD;
    uint32_t accLength;
    uint32_t accHeading;
    uint8_t reserved2[4];
    uint32_t flags;
} s_ubx_msg_nav_relposned_t;
#pragma pack(pop)

typedef union
{
    s_ubx_msg_nav_pvt_t msg_nav_pvt;
    s_ubx_msg_nav_relposned_t msg_nav_relposned;
    uint8_t raw_data[UBX_RAW_DATA_BUFFER];
} u_ubx_msg_t;

#endif