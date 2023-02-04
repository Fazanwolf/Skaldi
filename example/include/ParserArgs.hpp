#ifndef PARSER_ARGS_HPP
#define PARSER_ARGS_HPP


#include <iostream>
#include <cstring>
#include "Skaldi.hpp"
#include "utilities/Utilities.hpp"

#define HELPER "Skaldi\n"\
"DESCRIPTION\n"\
"A C++ library that you can use to easily create server or client.\n\n"\
"USAGE\n"\
"    ./test [flag]"\
"         -h, --help      Display this help message.\n"\
"         -v, --version   Display the version of the library.\n"\
"    ./test base type [ip] port\n"\
"         base            The base network that you want, server or client.\n"\
"         type            The type of socket connection, TCP or UDP.\n"\
"         [ip]            The target ip, needed only for client base.\n"\
"         port            The port to use.\n\n" \
"EXAMPLES\n"\
"    ./test server udp 5000\n"                \
"    ./test client udp 0.0.0.0 5000\n"        \
"    ./test server tcp 5001\n"                \
"    ./test client tcp 0.0.0.0 5001\n\n"\
"Skaldi is a library free of use by anyone and developped by Fazanwolf.\n"

#define VERSION "Skaldi version 0.0.1"

#define INVALID_ARGS "Error: Invalid argument.\nTry -h or --help for more "    \
"information."

/**
 * ParserArgs Class
 * That class allow:
 * - Testing on the server side
 * - Testing on the client side
 */
class ParserArgs {
public:
    ParserArgs(int ac = 1, char **av = nullptr);
    ~ParserArgs();
    void handler();

protected:
    int basicArgs();
    int handleServer();
    int handlerClient();
    int invalidArgs();

private:
    int helper();
    int version();

    int _ac;
    char **_av;
    Skaldi::Skaldi *_g;
};

#endif //PARSER_ARGS_HPP
