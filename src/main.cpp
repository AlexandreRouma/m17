#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#include "lsf.h"
#include "crc16.h"

int main() {
    M17::LSF lsf;
    lsf.dst = M17_ADDR_BROADCAST;
    lsf.src = M17::encodeCall("ON5RYZ");
    lsf.type.stream = true;
    lsf.type.dataType = M17::DATA_TYPE_VOICE;
    lsf.type.encryption = M17::ENCRYPTION_NONE;
    lsf.type.can = 0;

    uint8_t buffer[M17_LSF_SIZE];
    M17::LSF::encode(lsf, buffer);

    bool valid = M17::LSF::decode(buffer, lsf);
    printf(valid ? "VALID" : "INVALID");

    for (int i = 0; i < M17_LSF_SIZE; i++) {
        printf("%02X ", buffer[i]);
    }
    printf("\n");

    return 0;
}