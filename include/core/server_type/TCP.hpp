#ifndef SKALDI_TCP_SERVER_HPP
#define SKALDI_TCP_SERVER_HPP

#include "spdlog/spdlog.h"
#include "core/IServer.hpp"

/**
 * @brief
 */
namespace sk::server {

    class TCP : public IServer {
    public:
        TCP(boost::asio::io_context &ioContext, unsigned short port);
        ~TCP() override;
        void sendToEveryone(const std::string &message) override;
        void getInput() override;
        void setBroadcasting(bool able) override;

        void broadcast(const int &id, const std::string &message) override;
        void receive() override;
        void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred) override;
    protected:

    private:
        void startAccept(boost::asio::io_context &ioContext);
        void handleAccept(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error);
        boost::asio::ip::tcp::acceptor _acceptor;
        bool _broadcasting;
    };
}

#endif //SKALDI_TCP_SERVER_HPP