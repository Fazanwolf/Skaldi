#ifndef SKALDI_HPP
#define SKALDI_HPP

#include <spdlog/spdlog.h>
#include "core/Server.hpp"
#include "core/Client.hpp"

namespace sk {

    /**
     * @brief Class Skaldi that will be used to create a client or a server
     * @tparam ClientType
     * @tparam ServerType
     */
    template<typename ClientType, typename ServerType>
    class Skaldi {
    public:
        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a client and a server
         * @param host
         * @param port
         */
        Skaldi(const std::string &host, unsigned short port)
        {
            client = new Client<ClientType>(_ioContext, host, std::to_string(port));
            server = new Server<ServerType>(_ioContext, port);
        }

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a client
         * @param host
         * @param port
         */
        Skaldi(const std::string &host, const std::string &port)
        {
            client = new Client<ClientType>(_ioContext, host, port);
        }

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a server
         * @param port
         */
        explicit Skaldi(unsigned short port)
        {
            server = new Server<ServerType>(_ioContext, port);
        }

        /**
         * @brief Destructor of Skaldi
         * @details Destructor of Skaldi that will delete the client or the server
         */
        ~Skaldi()
        {
            if (client != nullptr)
                delete client;
            if (server != nullptr)
                delete server;
        }

        boost::asio::io_context &getIoContext()
        {
            return _ioContext;
        }

        void run()
        {
            _ioContext.run();
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

        Client<ClientType> *client;
        Server<ServerType> *server;

    private:
        boost::asio::io_context _ioContext;
    };
};

#endif //SKALDI_HPP