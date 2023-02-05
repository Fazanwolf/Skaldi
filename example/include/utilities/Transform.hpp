#ifndef UTILITIES_TRANSFORM_HPP
#define UTILITIES_TRANSFORM_HPP

#include <algorithm>
#include <regex>
#include <iostream>

namespace utilities {

    class Transform {
    public:
        static void toUpper(std::string &str);
        static void toLower(std::string &str);
        static void trim(std::string &str);
    };

}

#endif //UTILITIES_TRANSFORM_HPP
