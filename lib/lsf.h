#pragma once
#include <stdint.h>
#include "address.h"
#include "gnss.h"

#define M17_LSF_SIZE    30

namespace M17 {
    enum DataType {
        DATA_TYPE_RSVD          = 0,
        DATA_TYPE_DATA          = 1,
        DATA_TYPE_VOICE         = 2,
        DATA_TYPE_VOICE_DATA    = 3
    };

    enum Encryption {
        ENCRYPTION_NONE     = 0,
        ENCRYPTION_AES      = 1,
        ENCRYPTION_SCAMBLER = 2,
        ENCRYPTION_OTHER    = 3
    };

    struct LSFType {
        bool stream;
        DataType dataType;
        Encryption encryption;
        uint8_t encryptionSubtype;
        uint8_t can;

        static uint16_t encode(const LSFType& lsfType);
        static LSFType decode(uint16_t lsfType);
    };

    struct LSF {
        Address dst;
        Address src;
        LSFType type;
        union {
            GNSS gnss;
            // ExtCallsign extCall;
        };

        static void encode(const LSF& lsf, uint8_t* data, bool encodeCRC = true);
        static bool decode(const uint8_t* data, LSF& lsf, bool checkCRC = true);
    };
}