#pragma once
#include <stdint.h>
#include <string>

#include "lsf.h"

#define M17_FRAME_SIZE      46
#define M17_META_SIZE       14

namespace M17 {
    enum Sync {
        SYNC_LSF    = 0x55F7,
        SYNC_BERT   = 0xDF55,
        SYNC_STREAM = 0xFF5D,
        SYNC_PACKET = 0x75FF
    };

    enum MetaContent {
        META_CONTENT_TEXT       = 0,
        META_CONTENT_GNSS       = 1,
        META_CONTENT_EXT_CALL   = 2,
        META_CONTENT_RSVD       = 3
    };

    struct ExtCallsign {
        std::string originator;
        std::string reflectorName;
    };

    class Encoder {
    public:
    private:
    };

    class Decoder {
    public:
    private:
    };
}