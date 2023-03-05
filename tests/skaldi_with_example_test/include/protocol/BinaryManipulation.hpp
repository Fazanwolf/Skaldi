#ifndef SKALDI_PROTOCOL_UTILITIES_BINARY_MANIPULATION_HPP
#define SKALDI_PROTOCOL_UTILITIES_BINARY_MANIPULATION_HPP

#include <iostream>

typedef std::string bytes;

namespace sk::proto {

    class BinaryManipulation {
    public:
        BinaryManipulation() = default;
        ~BinaryManipulation() = default;

        virtual bytes getPacket() const;
        virtual std::string getPacketASCII() const;

        virtual std::string toASCII();
        virtual bytes setBinaryBit(int idx, bool value);
        virtual bool checkPacketAt(int idx) const;

        static std::string binaryToASCII(const bytes &binary);
        static bytes asciiToBinary(const std::string &ascii);
        static bytes setBinaryBit(const bytes &binary, int idx, bool value);
        static bytes setBinaryBit(const bytes &binary, int idx, char value);
    private:
        bytes _packet;
    };

}

#endif //SKALDI_PROTOCOL_UTILITIES_BINARY_MANIPULATION_HPP
