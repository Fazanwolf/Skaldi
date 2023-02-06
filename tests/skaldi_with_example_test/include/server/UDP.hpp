#ifndef SKALDI_UDP_SERVER_HPP
#define SKALDI_UDP_SERVER_HPP

#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <map>

namespace Skaldi::server {

    /**
     * @brief UDP Server
     * @param io_service
     * @param port
     */
    class UDP {
    public:
        UDP(boost::asio::io_service &io_service, unsigned short port);
        ~UDP();
        void send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint);

    private:
        void receive();
        void handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred);
        void handleSend(const boost::system::error_code &error, boost::asio::ip::udp::endpoint &endpoint);

        unsigned short _nb_client;
        boost::asio::ip::udp::socket _socket;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        std::array<char, 1024> _buffer;
        std::map<boost::asio::ip::udp::endpoint, std::string> _clients;
    };
}

#endif //SKALDI_UDP_SERVER_HPP