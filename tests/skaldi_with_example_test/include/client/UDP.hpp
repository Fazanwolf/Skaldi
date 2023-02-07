#ifndef SKALDI_UDP_CLIENT_HPP
#define SKALDI_UDP_CLIENT_HPP

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <bitset>
#include <thread>
#include <iostream>

namespace sk::client {

    class UDP {
    public:
        UDP(boost::asio::io_service &io_service, const std::string &host, const std::string &port);
        ~UDP();
        void getInput();
        void send(const std::string &message);
        void receive();

    private:
        void handleSend(const boost::system::error_code &error, const std::string &message);
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);

        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::resolver _resolver;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        boost::array<char, 1024> _buffer;
    };
}

#endif //SKALDI_UDP_CLIENT_HPP