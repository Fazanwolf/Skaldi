#ifndef UTILITIES_CHECK_HPP
#define UTILITIES_CHECK_HPP

#include <iostream>
#include <regex>

namespace utilities {

    class Check {
    public:
        static bool isIp(const std::string &ip);
        static bool isPort(const std::string &port);
        static bool isAlias(const std::string &target, const std::string &flag, const std::string &alias);
        static bool strIsEqual(const std::string &src, const std::string &target);
    private:
        const std::regex _portPattern("^([1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
        const std::regex _ipPattern("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}$");
    };

}

#endif //UTILITIES_CHECK_HPP
