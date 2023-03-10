#include "golay24.h"

#define MESSAGE_BITS    12

namespace M17::golay24 {
    // Generator matrix with row order reversed for faster math
    uint32_t GEN_MATRIX[MESSAGE_BITS] = {
        0b000000000001100011101011,
        0b000000000010100100111110,
        0b000000000100101010010111,
        0b000000001000110111000110,
        0b000000010000001101100111,
        0b000000100000011011001101,
        0b000001000000110110011001,
        0b000010000000001111011010,
        0b000100000000011110110100,
        0b001000000000111101101000,
        0b010000000000011000111011,
        0b100000000000110001110101
    };

    uint32_t encodeChunk(uint16_t msg) {
        uint32_t code = 0;

        // Calculate parity bits using generator matrix
        for (int i = 0; i < MESSAGE_BITS; i++) {
            if ((msg >> i) & 1) { code ^= GEN_MATRIX[i]; }
        }

        return code;
    }

    uint16_t decodeChunk(uint32_t code) {
        // TODO
    }

    int encode(const uint8_t* in, uint8_t* out, int len) {
        // Make sure the input is a multiple of 12 bits
        if ((len * 2) % 3) { return -1; }

        // Encode chunks
        int oOffset = 0;
        int chunks = (len * 2) / 3;
        for (int i = 0; i < chunks; i++) {
            // Read 12bits of the input into a message
            int iOffset = (i * 3) / 2;
            uint16_t msg;
            if (i%2) {
                msg = ((uint16_t)in[iOffset] & 0xF) << 8;
                msg |= in[iOffset + 1];
            }
            else {
                msg = (uint16_t)in[iOffset] << 4;
                msg |= in[iOffset + 1] >> 4;
            }

            // Encode message
            uint32_t code = encodeChunk(msg);

            // Write to output
            out[oOffset] = code >> 16;
            out[oOffset + 1] = (code >> 8) & 0xFF;
            out[oOffset + 2] = code & 0xFF;
            oOffset += 3;
        }

        return len * 2;
    }

    int decode(const uint8_t* in, uint8_t* out, int len) {
        // Make sure the input is a multiple of 24 bits
        if (len % 3) { return -1; }

        // Decode chunks
        int iOffset = 0;
        int oOffset = 0;
        int chunks = len / 3;
        for (int i = 0; i < chunks; i++) {
            // Read 24bits of the input into a codeword
            uint32_t code = (uint32_t)in[iOffset] << 16;
            code |= (uint32_t)in[iOffset + 1] << 8;
            code |= in[iOffset + 2];
            iOffset += 3;

            // Decode code
            uint16_t msg = decodeChunk(code);

            // Write to output
            out[oOffset] = msg >> 8;
            out[oOffset + 1] = msg & 0xFF;
            oOffset += 2;
        }

        return len / 2;
    }
}