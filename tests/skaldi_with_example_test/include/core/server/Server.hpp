#ifndef SKALDI_SERVER_HPP
#define SKALDI_SERVER_HPP

#include "core/server/IServer.hpp"
#include "core/server/IP/TCP.hpp"
#include "core/server/IP/UDP.hpp"

namespace sk {

    template <typename T>
    class Server : public IServer {
    public:

        Server()
        {
            _server = nullptr;
        }

        explicit Server(unsigned short port)
        {
            _server = std::make_shared<T>(_ioContext, port);
        }

        virtual ~Server() override
        {
        }

        void send(const std::string &message, boost::asio::ip::udp::endpoint &endpoint)
        {
            _server->send(message, endpoint);
        }

        void sendToEveryone(const std::string &message) override
        {
            _server->sendToEveryone(message);
        }

        void getInput() override
        {
            _server->getInput();
        }

        void setBroadcasting(bool able) override
        {
            _server->setBroadcasting(able);
        }

        void receive() override
        {
            _server->receive();
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

        Server &operator=(Server other)
        {
            if (!other._ioContext.stopped())
                other._ioContext.stop();
            _server = other._server;
            return *this;
        }

    protected:
    private:
        boost::asio::io_context _ioContext;
        std::shared_ptr<T> _server;
    };

}

#endif //SKALDI_SERVER_HPP
