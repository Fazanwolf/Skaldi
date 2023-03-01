#ifndef SKALDI_TCP_CLIENT_HPP
#define SKALDI_TCP_CLIENT_HPP

#include "spdlog/spdlog.h"
#include "core/client/IClient.hpp"
#include <iostream>

namespace sk::client {

    /**
     * @brief Class TCP client
     * @details Class TCP client that will be used to send and receive messages
     */
    class TCP : public IClient {
    public:
        /**
         * @brief Constructor of the TCP client
         * @details Constructor of the TCP client that will create a socket and a resolver to connect to the server
         * @param ioContext
         * @param host
         * @param port
         */
        TCP(std::shared_ptr<boost::asio::io_context> ioContext, const std::string &host, const std::string &port);
        /**
         * @brief Destructor of the TCP client
         * @details Destructor of the TCP client that will close the socket
         */
        virtual ~TCP() override;
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
         * @brief Send a message to the server
         * @details Send a message to the server from an instance of the client
         * @param client
         * @param message
         * @return void
         */
        static void send(TCP *client, const std::string &message);
        /**
         * @brief Receive a message from the server
         * @details Receive a message from the server
         * @return void
         */
        void receive() override;
        /**
         * @brief Set the debugging mode
         * @details Set the debugging mode
         * @param isDebugging
         * @return void
         */
        void setDebugging(bool isDebugging) override;
        /**
         * @brief Get the buffer
         * @details Get the buffer
         * @return std::string
         */
        std::string getBuffer() override;

    protected:
        /**
         * @brief Handle sent messages
         * @details Handle sent messages
         * @param error
         * @param message
         * @return void
         */
        void handleSend(const boost::system::error_code &error, const std::string &message);
        /**
         * @brief Handle received messages
         * @details Handle received messages
         * @param error
         * @param len
         * @return void
         */
        void handleReceive(const boost::system::error_code &error);

    private:
        /**
         * @brief Socket of the client
         * @details Socket of the client that will be used to send and receive messages
         */
        boost::asio::ip::tcp::socket _socket;
        /**
         * @brief Buffer of the client
         * @details A buffer to store the messages received
         */
        boost::array<char, 1024> _buffer {};
        bool _isDebugging = false;
    };
}

#endif //SKALDI_TCP_CLIENT_HPP