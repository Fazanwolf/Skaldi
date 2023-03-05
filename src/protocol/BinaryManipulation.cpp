#include "protocol/BinaryManipulation.hpp"

namespace sk::proto {
    
    bytes BinaryManipulation::getPacket() const
    {
        return _packet;
    }

    std::string BinaryManipulation::getPacketASCII() const
    {
        return binaryToASCII(_packet);
    }

    std::string BinaryManipulation::toASCII()
    {
        return binaryToASCII(_packet);
    }

    bytes BinaryManipulation::setBinaryBit(int idx, bool value)
    {
        return setBinaryBit(_packet, idx, value);
    }

    bool BinaryManipulation::checkPacketAt(int idx) const
    {
        return _packet[idx] == '1';
    }

    std::string BinaryManipulation::binaryToASCII(const bytes &binary)
    {
        std::string res;

        for (unsigned long i = 0; i < binary.size(); i += 8) {
            int ascii = 0;
            for (unsigned long  j = 0; j < 8; j++)
                ascii += (binary[i + j] - '0') * (1 << (7 - j));
            res += static_cast<char>(ascii);
        }

        return res;
    }

    bytes BinaryManipulation::asciiToBinary(const std::string &ascii)
    {
        bytes res;

        for (char c: ascii) {
            int asciiVal = static_cast<int>(c);
            std::string binary;
            for (int i = 7; i >= 0; i--)
                binary += (asciiVal & (1 << i)) ? '1' : '0';
            res += binary;
        }

        return res;
    }

    bytes BinaryManipulation::setBinaryBit(const bytes &binary, int idx, bool value)
    {
        bytes res = binary;

        res[idx] = (value ? '1' : '0');

        return res;
    }

    bytes BinaryManipulation::setBinaryBit(const bytes &binary, int idx, char value)
    {
        bytes res = binary;

        res[idx] = (value == '1' ? '1' : '0');

        return res;
    }

}
