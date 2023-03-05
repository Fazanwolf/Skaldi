#include "core/client/IP/UDP.hpp"

namespace sk::client {

    UDP::UDP(boost::asio::io_context &ioContext, const std::string &host, const std::string &port) : _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)), _resolver(ioContext)
    {
        const boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), host, port);
        const boost::asio::ip::udp::resolver::iterator endpoints = _resolver.resolve(query);
        _remoteEndpoint = *endpoints;
    }

    UDP::~UDP()
    {
        if (_socket.is_open())
            this->disconnect();
    }

    void UDP::setDebugging(bool isDebugging)
    {
        _debugging = isDebugging;
    }

    std::string UDP::getBuffer()
    {
        if (!_queueOfActions.empty()) {
            std::string data = _queueOfActions.front();
            _queueOfActions.pop();
            return data;
        }
        return "";
    }

    void UDP::connect(const std::string &data)
    {
        this->send(data);
    };

    void UDP::disconnect()
    {
        this->send(".");
        this->_resolver.cancel();
        this->_socket.close();
    }

    void UDP::getInput()
    {
        std::thread t([&]() {
            while (true) {
                std::string message;
                std::getline(std::cin, message);
                if (message == "exit") {
                    this->disconnect();
                    std::exit(0);
                }
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

    void UDP::handleSend(const boost::system::error_code &error, const std::string &message) const
    {
        if (!error) {
            if (_debugging) spdlog::info("[SEND] {}", message);
        }
    }

    void UDP::receive()
    {
        _socket.async_receive_from(boost::asio::buffer(_buffer), _remoteEndpoint,
                                   boost::bind(&UDP::handleReceive, this,
                                               boost::asio::placeholders::error
                                   )
        );
    }

    void UDP::handleReceive(const boost::system::error_code &error)
    {
        if (!error || error == boost::asio::error::message_size) {
            if (_buffer.data()[0] != '\0') {
                if (_debugging) spdlog::info("[RECEIVE] {}", _buffer.data());
                this->_queueOfActions.push(_buffer.data());
                _buffer.fill('\0');
            }
            return this->receive();
        }
        spdlog::error("Error sending data: {}", error.message());
    }


}
