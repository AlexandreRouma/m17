#pragma once
#include <stdint.h>

namespace M17 {
    enum DataSource {
        DATA_SOURCE_M17_CLIENT  = 0x00,
        DATA_SOURCE_OPENRTX     = 0x01,
        DATA_SOURCE_OTHER       = 0xFF
    };

    enum StationType {
        STATION_TYPE_FIXED      = 0x00,
        STATION_TYPE_MOBILE     = 0x01,
        STATION_TYPE_HANDHELD   = 0x02
    };

    struct GNSS {
        DataSource dataSource;
        StationType stationType;
        double latitude;
        double longitude;
        double altitude;
        double bearing;
        double speed;

        static void encode(const GNSS& gnss, uint8_t* data);
        static void decode(const uint8_t* data, GNSS& gnss);
    };
};