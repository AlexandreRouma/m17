#include "address.h"

namespace M17 {
    const char BASE40_ALPHA[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-/.";

    void encodeAddress(const Address& addr, uint8_t* data) {
        data[0] = (addr >> 40) & 0xFF;
        data[1] = (addr >> 32) & 0xFF;
        data[2] = (addr >> 24) & 0xFF;
        data[3] = (addr >> 16) & 0xFF;
        data[4] = (addr >> 8) & 0xFF;
        data[5] = addr & 0xFF;
    }

    Address decodeAddress(const uint8_t* data) {
        Address addr = (Address)data[0] << 40;
        addr |= (Address)data[1] << 32;
        addr |= (Address)data[2] << 24;
        addr |= (Address)data[3] << 16;
        addr |= (Address)data[4] << 8;
        addr |= (Address)data[5];
        return addr;
    }

    Address encodeCall(const std::string& call) {
        // Initialize address to 0
        int64_t addr = 0;
        
        // From end to start
        for (int i = call.size()-1; i >= 0; i--) {
            // Locate digit in alphabet
            char ch = std::toupper(call[i]);
            int64_t digit = -1;
            for (int j = 0; j < 40; j++) {
                if (BASE40_ALPHA[j] == ch) {
                    digit = j;
                    break;
                }
            }

            // Give up if digit is not in the alphabet
            if (digit < 0) { return -1; }

            // Shift address and add digit
            addr *= 40;
            addr += digit;
        }

        // Check if the address is a valid call
        if (addr < M17_ADDR_ID_MIN || addr > M17_ADDR_ID_MAX) {
            return M17_ADDR_INVALID;
        }

        return addr;
    }

    std::string decodeCall(Address addr) {
        // Check if the address is a valid call
        if (addr < M17_ADDR_ID_MIN || addr > M17_ADDR_ID_MAX) {
            return "";
        }

        // Initialize text to an empty string
        std::string call = "";

        while (addr) {
            // Extract digit
            uint64_t digit = (addr % 40);

            // Convert to ASCII
            call += BASE40_ALPHA[digit];

            // Remove digit and shift next digit in its place
            addr -= digit;
            addr /= 40;
        }

        return call;
    }
}