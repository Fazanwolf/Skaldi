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
            client = new Client<ClientType>(_ioService, host, std::to_string(port));
            server = new Server<ServerType>(_ioService, port);
        }

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a client
         * @param host
         * @param port
         */
        Skaldi(const std::string &host, const std::string &port)
        {
            client = new Client<ClientType>(_ioService, host, port);
        }

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a server
         * @param port
         */
        explicit Skaldi(unsigned short port)
        {
            server = new Server<ServerType>(_ioService, port);
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

        void run()
        {
            _ioService.run();
        }

        void runOne()
        {
            _ioService.run_one();
        }

        void poll()
        {
            _ioService.poll();
        }

        void pollOne()
        {
            _ioService.poll_one();
        }

        Client<ClientType> *client;
        Server<ServerType> *server;

    private:
        boost::asio::io_service _ioService;
    };
};

#endif //SKALDI_HPP