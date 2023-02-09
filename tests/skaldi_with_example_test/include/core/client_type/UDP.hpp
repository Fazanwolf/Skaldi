#ifndef SKALDI_UDP_CLIENT_HPP
#define SKALDI_UDP_CLIENT_HPP

#include "spdlog/spdlog.h"
#include "core/IClient.hpp"
#include <functional>

namespace sk::client {

    /**
     * @brief Class UDP client
     */
    class UDP : public IClient {
    public:
        /**
         * @brief Constructor of the UDP client
         * @details Constructor of the UDP client that will create a socket and a resolver to connect to the server
         * @param ioService
         * @param host
         * @param port
         */
        UDP(boost::asio::io_service &ioService, const std::string &host, const std::string &port);
        /**
         * @brief Destructor of the UDP client
         * @details Destructor of the UDP client that will close the socket
         */
        virtual ~UDP() override;
        /**
         * @brief Get the input of the user
         * @details Get the input of the user and send it to the server
         * @return void
         */
        void getInput() override;
        /**
         * @brief Send a message to the server
         * @details Send a message to the server
         * @param message
         * @return void
         */
        void send(const std::string &message) override;
        /**
         * @brief Send a message to the server from a pointer of the client
         * @details Send a message to the server
         * @param clt
         * @param message
         * @return void
         */
        static void send(UDP *clt, const std::string &message);
        /**
         * @brief Receive a message from the server
         * @details Receive a message from the server
         * @return void
         */
        void receive() override;
        void setDebugging(bool isDebugging) override;
        /**
         * @brief Enable or disable the first connection function
         * @details Enable or disable the first function passed as parameter when the client is connected to the server for the first time
         * @param isExecuted
         * @return void
         */
        void setFirstConnection(bool isExecuted) override;
        /**
         * @brief First connection into the server
         * @details Do the function passed as parameter when the client is connected to the server for the first time
         * @tparam R
         * @tparam Args
         * @param func
         * @param args
         */
        template<typename R, typename... Args> void firstConnection(std::function<R(Args...)> func, Args... args)
        {
            if (_isExecuted) func(args...);
        };

        /**
         * @brief Handle sent messages
         * @details Handle sent messages
         * @param error
         * @param message
         * @return void
         */
        void handleSend(const boost::system::error_code &error, const std::string &message) override;
        /**
         * @brief Handle received messages
         * @details Handle received messages
         * @param error
         * @param bytesTransferred
         * @return void
         */
        void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred) override;
    protected:

    private:
        /**
         * @brief Socket of the client
         * @details Socket of the client
         */
        boost::asio::ip::udp::socket _socket;
        /**
         * @brief Resolver of the client
         * @details Resolver of the client
         */
        boost::asio::ip::udp::resolver _resolver;
        /**
         * @brief Endpoint of the server
         * @details Keep the endpoint of the server to send messages
         */
        boost::asio::ip::udp::endpoint _remoteEndpoint;
        /**
         * @brief Buffer of the client
         * @details A buffer to store the messages received
         */
        boost::array<char, 1024> _buffer {};
        bool _isExecuted = false;
        bool _isDebugging = false;
    };
}

#endif //SKALDI_UDP_CLIENT_HPP