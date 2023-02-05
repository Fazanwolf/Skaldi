//
// Created by fazanwolf on 1/9/23.
//

#ifndef SKALDI_HPP
#define SKALDI_HPP

#include <iostream>

#include <spdlog/spdlog.h>

#include "server/TCP.hpp"
#include "server/UDP.hpp"
#include "client/TCP.hpp"
#include "client/UDP.hpp"

namespace Skaldi {

    class Skaldi {
    public:
        Skaldi();
        ~Skaldi() = default;
        void createUDPServer(unsigned short port);
        void createTCPServer(unsigned short port);
        void createUDPClient(const std::string &ip, const std::string &port);
        void createTCPClient(std::string ip, unsigned short port);

        server::UDP *_udp_srv;
        server::TCP *_tcp_srv;
        client::UDP *_udp_clt;
        client::TCP *_tcp_clt;
    private:
        boost::asio::io_service _io_service;
    };
};

#endif //SKALDI_HPP