#pragma once
#include <stdint.h>

namespace M17 {
    /**
     * Calculate or check CRC16.
     * @param data Data or check or calculate CRC. When calculating, the space where the CRC is place shall be zeros.
     * @return Calculated CRC. When checking, it should be zero if correct.
     */
    uint16_t crc16(const uint8_t* data, int len);
}