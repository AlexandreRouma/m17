#pragma once
#include <stdint.h>

namespace M17::golay24 {
    /**
     * Encode a message using a Golay24 linear code.
     * @param in Input data, must be a multiple of 12 bits.
     * @param out Output buffer to write encoded message to.
     * @param len Length of the input in bytes.
     * @return Length of the output in bytes or -1 on error.
     */
    int encode(const uint8_t* in, uint8_t* out, int len);

    /**
     * Decode a message using a Golay24 linear code.
     * @param in Input data, must be a multiple of 24 bits.
     * @param out Output buffer to write decoded message to.
     * @param len Length of the input in bytes.
     * @return Length of the output in bytes or -1 on error.
     */
    int decode(const uint8_t* in, uint8_t* out, int len);
};