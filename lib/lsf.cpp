#include "lsf.h"
#include "crc16.h"

namespace M17 {
    uint16_t LSFType::encode(const LSFType& lsfType) {
        uint16_t _lsfType = lsfType.stream;
        _lsfType |= lsfType.dataType << 1;
        _lsfType |= lsfType.encryption << 3;
        _lsfType |= (lsfType.encryptionSubtype & 0b11) << 5;
        _lsfType |= (lsfType.can & 0b1111) << 7;
        return _lsfType;
    }

    LSFType LSFType::decode(uint16_t lsfType) {
        LSFType _lsfType;
        _lsfType.stream = lsfType & 1;
        _lsfType.dataType = (DataType)((lsfType >> 1) & 0b11);
        _lsfType.encryption = (Encryption)((lsfType >> 3) & 0b11);
        _lsfType.encryptionSubtype = (lsfType >> 5) & 0b11;
        _lsfType.can = (lsfType >> 7) & 0b1111;
        return _lsfType;
    }

    void LSF::encode(const LSF& lsf, uint8_t* data, bool encodeCRC) {
        M17::encodeAddress(lsf.dst, &data[0]);
        M17::encodeAddress(lsf.src, &data[6]);
        uint16_t type = LSFType::encode(lsf.type);
        data[12] = type >> 8;
        data[13] = type & 0xFF;
        // TODO: Encode meta

        // Calculate and encode CRC if needed
        if (encodeCRC) {
            data[28] = 0;
            data[29] = 0;
            uint16_t crc = crc16(data, M17_LSF_SIZE);
            data[28] = crc >> 8;
            data[29] = crc & 0xFF;
        }
    }

    bool LSF::decode(const uint8_t* data, LSF& lsf, bool checkCRC) {
        // Check CRC before attempting a decode
        if (checkCRC && crc16(data, M17_LSF_SIZE)) { return false; }

        // Decode
        lsf.dst = M17::decodeAddress(&data[0]);
        lsf.src = M17::decodeAddress(&data[6]);
        uint16_t type = (uint16_t)data[12] << 8;
        type |= data[13];
        
        // TODO: Decode meta

        return true;
    }
}