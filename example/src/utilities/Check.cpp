#include "utilities/Check.hpp"

namespace utilities {

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
            if (std::strcmp(target.c_str(), flag.c_str()) == 0 || std::strcmp(target.c_str(), alias.c_str()) == 0)
                return true;
            return false;
        }

        bool Check::strIsEqual(const std::string &src, const std::string &target)
        {
            if (std::strcmp(src.c_str(), target.c_str()) == 0)
                return true;
            return false;
        }

}