#include "crc16.h"
#include <stdio.h>

#define M17_CRC16_POLY      0x5935
#define M17_CRC16_INIT      0x36E6
// Note: The init value is the one after the rolling init to save compute time...

namespace M17 {
    uint16_t crc16(const uint8_t* data, int len) {
        // Initialize register
        uint16_t reg = M17_CRC16_INIT;

        // Perform polynomial division of data by the generator poly
        const int bits = len * 8;
        for (int i = 0; i < bits; i++) {
            // Get input bit
            uint16_t ibit = (data[i>>3] >> (7 - (i&7))) & 1;

            // Save output bit
            uint16_t obit = (reg >> 15);
            
            // Shift in data and xor depending on output
            reg = (reg << 1) | ibit;
            if (obit) { reg ^= M17_CRC16_POLY; }
        }

        return reg;
    }
}