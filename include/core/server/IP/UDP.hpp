#ifndef SKALDI_UDP_SERVER_HPP
#define SKALDI_UDP_SERVER_HPP

#include "spdlog/spdlog.h"
#include "core/server/IServer.hpp"

/**
 * @brief Namespace skaldi
 * @details Namespace skaldi
 */
namespace sk::server {

    /**
     * @brief UDP Server
     * @details UDP Async Server that will be used to send and receive messages
     * @param io_service
     * @param port
     */
    class UDP : public IServer {
        public:
            /**
             * @brief Constructor of the UDP Server
             * @details Constructor of the UDP Server that will create a socket and a resolver to connect to the server
             * @param ioContext
             * @param port
             */
            UDP(boost::asio::io_context &ioContext, unsigned short port);
            /**
             * @brief Destructor of the UDP Server
             * @details Destructor of the UDP Server that will close the socket
             */
            virtual ~UDP() override;
            /**
             * @brief Send a message to a client
             * @details Send a message to a client using an instance of the server
             * @param message
             * @param endpoint
             * @return void
             */
            void send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint);
            /**
             * @brief Send a message to everyone
             * @details Send a message to everyone using an instance of the server
             * @param message
             * @return void
             */
            void sendToEveryone(const std::string &message) override;
            /**
             * @brief Get the input of the user
             * @details Get the input of the user and send it to the server
             * @return void
             */
            void getInput() override;
            /**
             * @brief Set broadcasting
             * @details Enable or disable the broadcasting
             * @param able
             * @return void
             */
            void setBroadcasting(bool able) override;

            /**
             * @brief Receive a message from clients
             * @details Receive a message from clients
             * @return void
             */
            void receive() override;
        protected:
            /**
             * @brief Broadcast a message to everyone
             * @details Broadcast a message to everyone using an instance of the server
             * @param id
             * @param message
             * @return void
             */
            void broadcast(const int &id, const std::string &message);
            /**
             * @brief Handle the reception of a message
             * @details Handle the reception of a message using an instance of the server
             * @param error
             * @param bytesTransferred
             * @return void
             */
            void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred);
            /**
             * @brief Handle the sending of a message
             * @details Handle the sending of a message using an instance of the server
             * @param error
             * @param endpoint
             * @param message
             * @return void
             */
            void handleSend(const boost::system::error_code &error, boost::asio::ip::udp::endpoint &endpoint, const std::string &message);

        private:
            /**
             * @brief Number of clients
             * @details Number of clients connected to the server
             */
            unsigned short _nbClient;
            /**
             * @brief Socket
             * @details Socket of the server
             */
            boost::asio::ip::udp::socket _socket;
            /**
             * @brief Endpoint of client
             * @details Endpoint of client
             */
            boost::asio::ip::udp::endpoint _remoteEndpoint;
            /**
             * @brief Buffer
             * @details Buffer to receive messages
             */
            std::array<char, 1024> _buffer{};
            /**
             * @brief Broadcasting
             * @details Determine if the Broadcasting of the server is enabled or not
             */
            bool _broadcasting;
            /**
             * @brief Clients
             * @details Map of Clients connected to the server
             */
            std::map<boost::asio::ip::udp::endpoint, int> _clients;
    };
}

#endif //SKALDI_UDP_SERVER_HPP