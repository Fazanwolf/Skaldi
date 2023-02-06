#include "server/UDP.hpp"

namespace Skaldi::server {

    UDP::UDP(boost::asio::io_service &io_service, unsigned short port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        _nb_client = 0;
        spdlog::info("UDP Server started {} on port {} ", _remote_endpoint.address().to_string(), port);
        receive();
    }

    UDP::~UDP()
    {
        _socket.close();
    }

    void UDP::send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint)
    {
        _socket.async_send_to(boost::asio::buffer(message), endpoint,
                              boost::bind(&UDP::handleSend, this, boost::asio::placeholders::error, endpoint)
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

    void UDP::handleReceive(const boost::system::error_code &error, std::size_t bytes_transferred)
    {
        if (!error) {
            // Add the client endpoint to the map if it doesn't exist
            if (_clients.find(_remote_endpoint) == _clients.end()) {
                _clients[_remote_endpoint] = "clt" + std::to_string(_nb_client);
                send("Hello, " + _clients[_remote_endpoint], _remote_endpoint);
                spdlog::info("First connection of {}",  _clients[_remote_endpoint]);
                _nb_client++;
            }

            // Print the message received and the name of the client
            if (!error || error == boost::asio::error::message_size) {
                spdlog::info("Data received from {}: {}", _clients[_remote_endpoint], std::string(_buffer.data(), _buffer.data() + bytes_transferred));
            } else {
                spdlog::error("Error receiving data: {}", error.message());
            }

            // Send a message back to the client
            receive();
        }
    }

    void UDP::handleSend(const boost::system::error_code &error, boost::asio::ip::udp::endpoint &endpoint)
    {
        if (!error) {
            spdlog::info("Data send to {}", _clients[endpoint]);
        }
    }

}