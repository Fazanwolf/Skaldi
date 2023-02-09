#include "core/client_type/UDP.hpp"

namespace sk::client {

    UDP::UDP(boost::asio::io_context &ioContext, const std::string &host, const std::string &port) : _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), _resolver(ioContext)
    {
        const boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        const boost::asio::ip::udp::resolver::iterator endpoints = _resolver.resolve(query);
        _remoteEndpoint = *endpoints;
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
        _socket.async_send_to(boost::asio::buffer(message), _remoteEndpoint,
                              boost::bind(&UDP::handleSend, this,
                                          boost::asio::placeholders::error,
                                          message
                              )
        );
    }

    void UDP::send(UDP *clt, const std::string &message)
    {
        clt->_socket.async_send_to(boost::asio::buffer(message), clt->_remoteEndpoint,
                              boost::bind(&UDP::handleSend, clt,
                                          boost::asio::placeholders::error,
                                          message
                              )
        );
    }

    void UDP::receive()
    {
        _socket.async_receive_from(boost::asio::buffer(_buffer), _remoteEndpoint,
                                   boost::bind(&UDP::handleReceive, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred
                                   )
        );
    }

    void UDP::setDebugging(bool isDebugging)
    {
        _debugging = isDebugging;
    };

    void UDP::setFirstConnection(bool isExecuted)
    {
        _isExecuted = isExecuted;
    };

    void UDP::handleSend(const boost::system::error_code &error, const std::string &message)
    {
        if (!error) {
            if (_debugging) spdlog::info("Data send: {}", message);
//            return this->receive();
        }
    }

    std::string UDP::getBuffer()
    {
        return std::string(_buffer.data());
    };

    void UDP::handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred)
    {
        if (!error || error == boost::asio::error::message_size) {
            const std::string message(_buffer.data(), _buffer.data() + bytesTransferred);
            if (_debugging)
                spdlog::info("Server send: {}", message);
            else
                std::cout << message << std::endl;
            return this->receive();
        }
    }

}