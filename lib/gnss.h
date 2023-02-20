#pragma once
#include <stdint.h>

#define M17_GNSS_SIZE   14

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

        /**
         * Encode GNSS information to bytes.
         * @param gnss GNSS information.
         * @param data Buffer to encode the GNSS information to. Must be at least 14 bytes.
         */
        static void encode(const GNSS& gnss, uint8_t* data);

        /**
         * Decode GNSS information from bytes.
         * @param data Buffer to decode the GNSS information from. Must be at least 14 bytes.
         * @param gnss Decoded GNSS information.
         */
        static void decode(const uint8_t* data, GNSS& gnss);
    };
};