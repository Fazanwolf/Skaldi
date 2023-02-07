#include "server/TCP.hpp"

namespace sk::server {

    TCP::TCP(boost::asio::io_service &io_service, unsigned short port) : _io_service(io_service), _acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        startAccept();
    }

    void TCP::startAccept()
    {
        boost::shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(_io_service));

        _acceptor.async_accept(*socket, boost::bind(&TCP::handleAccept, this, socket, boost::asio::placeholders::error));
    }

    void TCP::handleAccept(boost::shared_ptr<boost::asio::ip::tcp::socket> socket, const boost::system::error_code &error)
    {
        if (!error) {
            std::cout << "Accepted connection from " << socket->remote_endpoint().address() << std::endl;
        }
        startAccept();
    }

    std::string TCP::getAddressFromLocalEndpoint()
    {
        auto endpoint = _acceptor.local_endpoint();
        return endpoint.address().to_string();
    }

    void TCP::setBroadcasting(bool able)
    {
        this->_broadcasting = able;
    }
}