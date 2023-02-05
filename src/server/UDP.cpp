#include "server/UDP.hpp"

namespace Skaldi::server {

    UDP::UDP(boost::asio::io_service &io_service, unsigned short port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
    {
        spdlog::info("UDP Server started {} on port {} ", _remote_endpoint.address().to_string(), port);
        receive();
    }

    UDP::~UDP()
    {
        _socket.close();
    }

    void UDP::send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint)
    {
        boost::array<char, 1024> send_buf;
        std::copy(message.begin(), message.end(), send_buf.begin());
        _socket.async_send_to(boost::asio::buffer(send_buf), endpoint,
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
                _clients[_remote_endpoint] = "Client";
            }

            // Print the message received and the name of the client
            spdlog::info("Data received from {}: {}", _clients[_remote_endpoint], std::string(_buffer.data(), _buffer.data() + bytes_transferred));

            // Send a message back to the client
            send("Hello, " + _clients[_remote_endpoint], _remote_endpoint);
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