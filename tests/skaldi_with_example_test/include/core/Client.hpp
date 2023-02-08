#ifndef SKALDI_CLIENT_HPP
#define SKALDI_CLIENT_HPP

#include "core/client_type/TCP.hpp"
#include "core/client_type/UDP.hpp"

namespace sk {

    /**
     * @brief Class Client
     * @details Class Client that will be used to send and receive messages
     * @tparam ClientType UDP or TCP
     */
    template<typename ClientType>
    class Client : public IClient {
    public:
        /**
         * @brief Constructor of the client
         * @details Constructor of the client that will create a socket and a resolver to connect to the server depending on the type of the client
         * @param type UDP or TCP
         * @param ioService Asio io_service
         * @param host IP address of the server
         * @param port Port of the server
         */
        Client(boost::asio::io_service &ioService, const std::string &host, const std::string &port)
        {
            _client = new ClientType(ioService, host, port);
        }

        /**
         * @brief Destructor of the client
         * @details Destructor of the client that will close the socket
         * @return void
         */
        virtual ~Client() override
        {
            if (_client != nullptr)
                delete _client;
        }

        /**
         * @brief Get the input of the user
         * @details Get the input of the user and send it to the server
         * @return void
         */
        void getInput() override
        {
            _client->getInput();
        }

        /**
         * @brief Send a message to the server
         * @details Send a message to the server using an instance of the client
         * @param message
         * @return void
         */
        void send(const std::string &message) override
        {
            _client->send(message);
        }

        /**
         * @brief Send a message to the server
         * @details Send a message to the server using an instance of the client
         * @return void
         */
        void receive() override
        {
            _client->receive();
        }

    protected:
        /**
         * @brief Handle sent messages
         * @details Handle sent messages
         * @param error
         * @param message
         * @return void
         */
        void handleSend(const boost::system::error_code &error, const std::string &message) override
        {
            _client->handleSend(error, message);
        }

        /**
         * @brief Handle received messages
         * @details Handle received messages
         * @param error
         * @param bytesTransferred
         */
        void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred) override
        {
            _client->handleReceive(error, bytesTransferred);
        }

    private:
        /**
         * @brief Instance of the client
         * @details Instance of the client that will be used to send and receive messages
         */
        ClientType *_client;
    };
}

#endif //SKALDI_CLIENT_HPP