#include "core/client_type/TCP.hpp"

namespace sk::client {

    TCP::TCP(boost::asio::io_context &ioContext, const std::string &host, const std::string &port) : _socket(ioContext)
    {
        boost::asio::ip::tcp::resolver resolver(ioContext);
        auto endpoints = resolver.resolve({host, port});

        boost::asio::connect(_socket, endpoints);
    }

    TCP::~TCP()
    {
        _socket.close();
    }

    void TCP::getInput()
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

    void TCP::send(const std::string &message)
    {
    }

    void TCP::send(TCP *clt, const std::string &message)
    {
    }

    void TCP::receive()
    {
    }

    void TCP::setDebugging(bool isDebugging)
    {
        _isDebugging = isDebugging;
    };

    void TCP::setFirstConnection(bool isExecuted)
    {
        _isExecuted = isExecuted;
    };

    std::string TCP::getBuffer()
    {
        return std::string(_buffer.data());
    };

    void TCP::handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred)
    {
    }

    void TCP::handleSend(const boost::system::error_code &error, const std::string &message)
    {
    }

}