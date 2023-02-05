#include "client/UDP.hpp"

namespace Skaldi::client {

    UDP::UDP(boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), _resolver(io_service)
    {
        boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        boost::asio::ip::udp::resolver::iterator endpoints = _resolver.resolve(query);
        _remote_endpoint = *endpoints;
    }

    UDP::~UDP()
    {
        _socket.close();
    }

    void UDP::send(const std::string &message)
    {
        boost::array<char, 1024> send_buf;
        std::copy(message.begin(), message.end(), send_buf.begin());
        _socket.async_send_to(boost::asio::buffer(send_buf), _remote_endpoint,
                              boost::bind(&UDP::handleSend, this,
                                          boost::asio::placeholders::error
                              )
        );
    }

    void UDP::receive()
    {
        _socket.async_receive_from(boost::asio::buffer(_buffer), _remote_endpoint,
                                   boost::bind(&UDP::handleReceive, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred
                                   )
        );
    }

    void UDP::handleSend(const boost::system::error_code &error)
    {
        if (!error) {
            spdlog::info("Data send.");
            this->receive();
        }
    }

    void UDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == boost::asio::error::message_size) {
            spdlog::info("Data received {}", std::string(_buffer.data(), _buffer.data() + bytes_transferred));
            this->receive();
        }
    }

}