#ifndef SKALDI_CLIENT_HPP
#define SKALDI_CLIENT_HPP

#include "core/client/IClient.hpp"
#include "core/client/IP/UDP.hpp"

namespace sk {

    /**
     * @brief Class Client
     * @details Class Client that will be used to send and receive messages
     * @tparam ClientType UDP or TCP
     */
    template<typename T>
    class Client : public IClient {
    public:
        Client()
        {
            _client = nullptr;
        }
        /**
         * @brief Constructor of the client
         * @details Constructor of the client that will create a socket and a resolver to connect to the server depending on the type of the client
         * @param host IP address of the server
         * @param port Port of the server
         */
        Client(const std::string &host, const std::string &port)
        {
            _client = std::make_shared<T>(_ioContext, host, port);
        };

        /**
         * @brief Destructor of the client
         * @details Destructor of the client that will close the socket
         * @return void
         */
        ~Client() override
        {
        };

        /**
         * @brief Get the input of the user
         * @details Get the input of the user and send it to the server
         * @return void
         */
        void getInput() override
        {
            _client->getInput();
        };

        /**
         * @brief Send a message to the server
         * @details Send a message to the server using an instance of the client
         * @param message
         * @return void
         */
        void send(const std::string &message) override
        {
            _client->send(message);
        };

        /**
         * @brief Send a message to the server
         * @details Send a message to the server using an instance of the client
         * @return void
         */
        void receive() override
        {
            _client->receive();
        };
        void setDebugging(bool isDebugging) override
        {
            _client->setDebugging(isDebugging);
        };
        /**
         * @brief Connect into the server
         * @details Connect into the server and send the data of identification
         * @param data
         */
        void connect(const std::string &data) override
        {
            _client->connect(data);
        };
        /**
         * @brief Disconnect from the server
         * @details Disconnect send the packet of disconnection to the server
         * @return void
         */
        void disconnect() override
        {
            _client->disconnect();
            _ioContext.stop();
        };
        /**
         * @brief Get buffer of the client
         * @details Get buffer of the client
         * @return Buffer of the client
         */
        std::string getBuffer() override
        {
            return _client->getBuffer();
        };

        void run()
        {
            std::thread t([&]() {
                _ioContext.run();
            });
            t.detach();
        }

        void runOne()
        {
            _ioContext.run_one();
        }

        void pollOne()
        {
            _ioContext.poll_one();
        }

        void poll()
        {
            _ioContext.poll();
        }

        Client &operator=(Client other)
        {
            _ioContext = other._ioContext;
            _client = other._client;
            return *this;
        }

    private:
        boost::asio::io_context _ioContext;
        /**
         * @brief Instance of the client
         * @details Instance of the client that will be used to send and receive messages
         */
        std::shared_ptr<T> _client;
    };
}

#endif //SKALDI_CLIENT_HPP
