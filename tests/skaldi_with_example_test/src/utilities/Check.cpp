#include "utilities/Check.hpp"

namespace utilities {

    const std::regex Check::_portPattern = std::regex("^([1-9][0-9]{0,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
    const std::regex Check::_ipPattern = std::regex("^((25[0-5]|(2[0-4]|1\\d|[1-9]|)\\d)\\.?\\b){4}$");

    bool Check::isIp(const std::string &ip)
    {
        if (std::regex_match(ip, _ipPattern) || ip == "localhost")
            return true;
        return false;
    }

    bool Check::isPort(const std::string &port)
    {
        if (std::regex_match(port, _portPattern))
            return true;
        return false;
    }

    bool Check::isAlias(const std::string &target, const std::string &flag, const std::string &alias)
    {
        if (target == flag || target == alias)
            return true;
        return false;
    }

}