#include "core/server_type/TCP.hpp"

namespace sk::server {

    TCP::TCP(boost::asio::io_service &ioService, unsigned short port) : _acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        startAccept(ioService);
    }

    TCP::~TCP()
    {
    }

    void TCP::startAccept(boost::asio::io_service &ioService)
    {
        boost::shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(ioService));

        _acceptor.async_accept(*socket, boost::bind(&TCP::handleAccept, this, socket, boost::asio::placeholders::error));
    }

    void TCP::handleAccept(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error)
    {
        if (!error) {
            std::cout << "Accepted connection from " << socket->remote_endpoint().address() << std::endl;
        }
//        startAccept();
    }

    void TCP::sendToEveryone(const std::string &message)
    {
    }

    void TCP::getInput()
    {
    }

    void TCP::setBroadcasting(bool able)
    {
        this->_broadcasting = able;
    }

    void TCP::broadcast(const int &id, const std::string &message)
    {
    }

    void TCP::receive()
    {
    }

    void TCP::handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred)
    {
    }


}