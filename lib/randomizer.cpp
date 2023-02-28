#include "randomizer.h"

#define RAND_SEQ_LEN    46

namespace M17 {
    const uint8_t RAND_SEQ[RAND_SEQ_LEN] = {
        // TODO
    };

    void randomizer(const uint8_t* in, uint8_t* out, int len) {
        int rand = 0;
        for (int i = 0; i < len; i++) {
            // XOR with random sequence
            out[i] = in[i] ^ RAND_SEQ[rand];

            // Increment counter and roll around if too high
            rand = (++rand >= RAND_SEQ_LEN) ? 0 : rand;
        }
    }
}