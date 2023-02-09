#include "core/server_type/UDP.hpp"

namespace sk::server {

    UDP::UDP(boost::asio::io_context &ioContext, unsigned short port) : _socket(ioContext, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        _nbClient = 0;
        _broadcasting = false;
        spdlog::info("UDP Server started {} on port {} ", _remoteEndpoint.address().to_string(), port);
        this->receive();
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
                this->sendToEveryone(message);
            }
        });
        t.detach();
    }

    void UDP::send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint)
    {
        _socket.async_send_to(boost::asio::buffer(message), endpoint,
                              boost::bind(&UDP::handleSend, this, boost::asio::placeholders::error, endpoint, message)
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

    void UDP::setBroadcasting(bool able)
    {
        this->_broadcasting = able;
    }

    void UDP::broadcast(const int &id, const std::string &message)
    {
        if (_broadcasting) {
            for (auto &[key, val]: _clients) {
                if (val != id) {
                    boost::asio::ip::udp::endpoint endpoint = key;
                    this->send(std::to_string(id) + " " + message, endpoint);
                }
            }
        }
    }

    void UDP::sendToEveryone(const std::string &message)
    {
        for (auto &[key, val]: _clients) {
            boost::asio::ip::udp::endpoint endpoint = key;
            this->send(message, endpoint);
        }
    }

    void UDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (!error) {
            // Add the client endpoint to the map if it doesn't exist
            if (_clients.find(_remoteEndpoint) == _clients.end()) {
                _clients[_remoteEndpoint] = _nbClient;
                send(std::to_string(_clients[_remoteEndpoint]), _remoteEndpoint);
                spdlog::info("First connection of {}",  _clients[_remoteEndpoint]);
                _nbClient++;
            }

            // Print the message received and the name of the client
            if (!error || error == boost::asio::error::message_size) {
                this->broadcast(_clients[_remoteEndpoint], std::string(_buffer.data(), _buffer.data() + bytes_transferred));
//                if (bytes_transferred <= 3) {
//                    spdlog::info("Bitset received from {}: {}", _clients[_remoteEndpoint], std::string(_buffer.data(), _buffer.data() + bytes_transferred));
//                    return receive();
//                }
                spdlog::info("Data received from {}: {}", _clients[_remoteEndpoint], std::string(_buffer.data(), _buffer.data() + bytes_transferred));
                return receive();
            }
        }
        spdlog::error("Error receiving data: {}", error.message());
        // Send a message back to the client
        return receive();
    }

    void UDP::handleSend(const boost::system::error_code &error, boost::asio::ip::udp::endpoint &endpoint, const std::string &message)
    {
        if (!error) {
            spdlog::info("Data send to {}: {}", _clients[endpoint], message);
        }
    }

}