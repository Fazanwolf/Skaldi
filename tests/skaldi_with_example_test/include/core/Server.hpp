#ifndef SKALDI_SERVER_HPP
#define SKALDI_SERVER_HPP

#include "core/server_type/UDP.hpp"
#include "core/server_type/TCP.hpp"

namespace sk {

    template <typename ServerType>
    class Server : public IServer {
    public:
        Server(boost::asio::io_context &ioContext, unsigned short port)
        {
            _server = new ServerType(ioContext, port);
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
        ServerType *_server;
    };

}

#endif //SKALDI_SERVER_HPP
