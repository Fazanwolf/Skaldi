#ifndef UTILITIES_CHECK_HPP
#define UTILITIES_CHECK_HPP

#include <iostream>
#include <cstring>
#include <regex>

namespace utilities {

    class Check {
    public:
        static bool isIp(const std::string &ip);
        static bool isPort(const std::string &port);
        static bool isAlias(const std::string &target, const std::string &flag, const std::string &alias);
        static bool strIsEqual(const std::string &src, const std::string &target);
    private:
        static const std::regex _portPattern;
        static const std::regex _ipPattern;
    };

}

#endif //UTILITIES_CHECK_HPP
