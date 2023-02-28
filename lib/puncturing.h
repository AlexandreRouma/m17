#pragma once
#include <stdint.h>

namespace M17::P1 {
    int puncture(const uint8_t* in, uint8_t* out, int len);
    int depuncture(const uint8_t* in, uint8_t* out, int len);
}

namespace M17::P2 {
    int puncture(const uint8_t* in, uint8_t* out, int len);
    int depuncture(const uint8_t* in, uint8_t* out, int len);
}

namespace M17::P3 {
    int puncture(const uint8_t* in, uint8_t* out, int len);
    int depuncture(const uint8_t* in, uint8_t* out, int len);
}