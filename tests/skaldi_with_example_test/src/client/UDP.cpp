#include "client/UDP.hpp"

namespace sk::client {

    UDP::UDP(boost::asio::io_service &io_service, const std::string &host, const std::string &port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), _resolver(io_service)
    {
        const boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        const boost::asio::ip::udp::resolver::iterator endpoints = _resolver.resolve(query);
        _remote_endpoint = *endpoints;
        this->send("new");
    }

    UDP::~UDP()
    {
        _socket.close();
    }

    void UDP::getInput()
    {
        std::thread t([&]() {
            while (true) {
                std::string message;
                std::getline(std::cin, message);
                if (message == "exit")
                    std::exit(0);
                this->send(message);
            }
        });
        t.detach();
    }

    void UDP::send(const std::string &message)
    {
        _socket.async_send_to(boost::asio::buffer(message), _remote_endpoint,
                              boost::bind(&UDP::handleSend, this,
                                          boost::asio::placeholders::error,
                                          message
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

    void UDP::handleSend(const boost::system::error_code &error, const std::string &message)
    {
        if (!error) {
            spdlog::info("Data send: {}", message);
            return this->receive();
        }
    }

    void UDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (!error || error == boost::asio::error::message_size) {
//            if (bytes_transferred <= 3) {
//                spdlog::info("Server send bitset: {}", std::string(_buffer.data(), _buffer.data() + bytes_transferred));
//                return this->receive();
//            }
            spdlog::info("Server send: {}", std::string(_buffer.data(), _buffer.data() + bytes_transferred));
            return this->receive();
        }
    }

}