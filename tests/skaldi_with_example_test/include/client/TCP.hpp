#ifndef SKALDI_TCP_CLIENT_HPP
#define SKALDI_TCP_CLIENT_HPP

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

namespace sk::client {

#include "boost/asio.hpp"
#include <iostream>

    class TCP {
    public:
        TCP(boost::asio::io_service &io_service, const std::string &host, unsigned short port);
        ~TCP() = default;
        void send(const std::string &message);
        std::string receive();

    private:
        boost::asio::ip::tcp::socket _socket;
    };
}

#endif //SKALDI_TCP_CLIENT_HPP