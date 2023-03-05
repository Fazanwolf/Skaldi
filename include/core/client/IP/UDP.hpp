#ifndef SKALDI_UDP_CLIENT_HPP
#define SKALDI_UDP_CLIENT_HPP

#include "spdlog/spdlog.h"
#include "core/client/IClient.hpp"
#include <functional>
#include <queue>

namespace sk::client {

    /**
     * @brief Class UDP client
     */
    class UDP : public IClient {
    public:
        /**
         * @brief Constructor of the UDP client
         * @details Constructor of the UDP client that will create a socket and a resolver to connect to the server
         * @param ioContext Asio io_context
         * @param host
         * @param port
         */
        UDP(boost::asio::io_context &ioContext, const std::string &host, const std::string &port);
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
//        /**
//         * @brief Send a message to the server from a pointer of the client
//         * @details Send a message to the server
//         * @param clt
//         * @param message
//         * @return void
//         */
//        static void send(UDP *clt, const std::string &message);
        /**
         * @brief Receive a message from the server
         * @details Receive a message from the server
         * @return void
         */
        void receive() override;
        /**
         * @brief Enable or disable the debugging mode
         * @details Enable or disable the debugging mode
         * @param isDebugging
         * @return void
         */
        void setDebugging(bool isDebugging) override;
        /**
         * @brief Connect into the server
         * @details Connect into the server and send the data of identification
         * @param data
         * @return void
         */
        void connect(const std::string &data) override;
        /**
         * @brief Disconnect into the server
         * @details Disconnect send the packet of disconnection
         * @param data
         * @return void
         */
        void disconnect() override;
        /**
         * @brief Get buffer of the client
         * @details Get buffer of the client
         * @return Buffer of the client
         */
        std::string getBuffer() override;

        /**
         * @brief Handle sent messages
         * @details Handle sent messages
         * @param error
         * @param message
         * @return void
         */
        void handleSend(const boost::system::error_code &error, const std::string &message) const;
        /**
         * @brief Handle received messages
         * @details Handle received messages
         * @param error
         * @param bytesTransferred
         * @return void
         */
        void handleReceive(const boost::system::error_code &error);
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
        std::queue<std::string> _queueOfActions;
        bool _debugging = false;
    };
}

#endif //SKALDI_UDP_CLIENT_HPP