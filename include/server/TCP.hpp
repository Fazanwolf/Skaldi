#ifndef SKALDI_TCP_SERVER_HPP
#define SKALDI_TCP_SERVER_HPP

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <memory>
#include <iostream>

namespace Skaldi::server {

    class TCP {
    public:
        TCP(boost::asio::io_service &io_service, unsigned short port);
        ~TCP() = default;

    private:
        void startAccept();
        void handleAccept(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error);
        std::string getAddressFromLocalEndpoint();
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::io_service &_io_service;
    };
}

#endif //SKALDI_TCP_SERVER_HPP