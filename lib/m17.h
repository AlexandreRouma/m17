#pragma once
#include <stdint.h>
#include <string>
#include <functional>

#include "lsf.h"

#define M17_SYNC_SYMS       8
#define M17_FRAME_SYMS      184

#define M17_FRAME_SIZE      46
#define M17_META_SIZE       14

#define M17_MIN_SYNC_CONF   0
#define M17_MAX_SYNC_CONF   4

namespace M17 {
    enum FrameType {
        FRAME_TYPE_LSF      = 0x55F7,
        FRAME_TYPE_BERT     = 0xDF55,
        FRAME_TYPE_STREAM   = 0xFF5D,
        FRAME_TYPE_PACKET   = 0x75FF
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

        void decode(float* syms, int count);

    private:
        void processLSFrame();
        void processBERTFrame();
        void processStreamFrame();
        void processPacketFrame();

        int8_t frameSoft[M17_FRAME_SYMS];
        uint8_t frame[M17_FRAME_SIZE];

    };
}