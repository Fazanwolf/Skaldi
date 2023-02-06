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
        void UDPServer(unsigned short port);
        void TCPServer(unsigned short port);

        void UDPClient(const std::string &ip, const std::string &port);
        void getInputUDPClient();

        void TCPClient(std::string ip, unsigned short port);

        void run();


        client::UDP *_udp_clt;
        client::TCP *_tcp_clt;
    private:
        boost::asio::io_service _io_service;
        server::UDP *_udp_srv;
        server::TCP *_tcp_srv;
    };
};

#endif //SKALDI_HPP