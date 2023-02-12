#ifndef SKALDI_HPP
#define SKALDI_HPP

#include <spdlog/spdlog.h>
#include "core/Server.hpp"
#include "core/Client.hpp"
#include "core/Type.hpp"

namespace sk {

    /**
     * @brief Class Skaldi that will be used to create a client or a server
     */
    template <type::InternetProtocol T>
    class Skaldi {
    public:

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a server
         * @param port
         */
        Skaldi(unsigned short port = 5000)
        {
            if (T == type::InternetProtocol::TCP)
                server = Server<type::Server::TCP>(_ioContext, port);
            if (T == type::InternetProtocol::UDP)
                server = Server<type::Server::UDP>(_ioContext, port);
        }

        /**
         * @brief Constructor of Skaldi
         * @details Constructor of Skaldi that will create a client
         * @param host
         * @param port
         */
        Skaldi(const std::string &host, const std::string &port)
        {
            if (T == InternetProtocol::TCP)
                client = Client<type::Client::TCP>(_ioContext, host, port);
            if (T == InternetProtocol::UDP)
                client = Client<type::Client::UDP>(_ioContext, host, port);
        }


        /**
         * @brief Destructor of Skaldi
         * @details Destructor of Skaldi that will delete the client or the server
         */
        ~Skaldi()
        {
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

//        NetworkType<InternetProtocol> *g;
        Client<ClientType> client;
        Server<ServerType> server;

    private:
        boost::asio::io_context _ioContext;
    };
};

#endif //SKALDI_HPP