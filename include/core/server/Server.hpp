#ifndef SKALDI_SERVER_HPP
#define SKALDI_SERVER_HPP

#include "core/server/IServer.hpp"
#include "core/server/IP/TCP.hpp"
#include "core/server/IP/UDP.hpp"

namespace sk {

    template <typename T>
    class Server : public IServer {
    public:
        explicit Server(unsigned short port)
        {
            _server = new T(_ioContext, port);
        }

        virtual ~Server() override
        {
            if (_server != nullptr)
                delete _server;
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

    protected:
        void broadcast(const int &id, const std::string &message) override
        {
            _server->broadcast(id, message);
        }

        void receive() override
        {
            _server->receive();
        }

        void handleReceive(const boost::system::error_code &error, std::size_t byesTransferred) override
        {
            _server->handleReceive(error, byesTransferred);
        }


    private:
        boost::asio::io_context _ioContext;
        T *_server;
    };

}

#endif //SKALDI_SERVER_HPP
