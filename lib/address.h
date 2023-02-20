#pragma once
#include <stdint.h>
#include <string>

#define M17_ADDR_SIZE       6

#define M17_ADDR_INVALID    0x000000000000
#define M17_ADDR_ID_MIN     0x000000000001
#define M17_ADDR_INFO       0x0000000ECDB9
#define M17_ADDR_ECHO       0x0000000ED87D
#define M17_ADDR_UNLINK     0x0000454F7745
#define M17_ADDR_ID_MAX     0xEE6B27FFFFFF
#define M17_ADDR_BROADCAST  0xFFFFFFFFFFFF

namespace M17 {
    typedef int64_t Address;

    /**
     * Encode address to bytes.
     * @param addr Address to be encoded.
     * @param data Buffer to write the encoded address to. Must be at least 6 bytes.
     */
    void encodeAddress(const Address& addr, uint8_t* data);

    /**
     * Decode address from bytes.
     * @param data Buffer decode the address from. Must be at least 6 bytes.
     * @return Address value.
     */
    Address decodeAddress(const uint8_t* data);

    /**
     * Encode callsign to address.
     * @param call Callsign string. Must only contain space, A->Z, 0->9, hyphene, forward slash and dot.
     * @return Address version of callsign.
     */
    Address encodeCall(const std::string& call);

    /**
     * Decode callsign from address.
     * @param addr 48bit address.
     * @return Callsign string.
     */
    std::string decodeCall(Address addr);
}