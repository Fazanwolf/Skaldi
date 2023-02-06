#include "client/TCP.hpp"

namespace Skaldi::client {

    TCP::TCP(boost::asio::io_service &io_service, const std::string &host, unsigned short port) : _socket(io_service)
    {
        boost::asio::ip::tcp::resolver resolver(io_service);
        auto endpoints = resolver.resolve({host, std::to_string(port)});

        boost::asio::connect(_socket, endpoints);
    }

    void TCP::send(const std::string &message)
    {
        boost::asio::write(_socket, boost::asio::buffer(message));
    }

    std::string TCP::receive()
    {
        boost::array<char, 1024> buffer;
        size_t len = _socket.read_some(boost::asio::buffer(buffer));
        return std::string(buffer.data(), len);
    }

}