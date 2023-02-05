#include "utilities/Transform.hpp"

namespace utilities {

    void Transform::toUpper(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    void Transform::toLower(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    void Transform::trim(std::string &str)
    {
        str = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
    }

}
