#include "Skaldi.hpp"

namespace sk {

    Skaldi::Skaldi()
    {
    }

    void Skaldi::UDPServer(unsigned short port)
    {
        _udp_srv = new server::UDP(_io_service, port);
    }

    void Skaldi::TCPServer(unsigned short port)
    {
        _tcp_srv = new server::TCP(_io_service, port);
    }

    void Skaldi::UDPClient(const std::string &ip, const std::string &port)
    {
        _udp_clt = new client::UDP(_io_service, ip, port);
    }

    void Skaldi::getInputUDPServer()
    {
        _udp_srv->getInput();
    }

    void Skaldi::getInputUDPClient() const
    {
        _udp_clt->getInput();
    }

    void Skaldi::run()
    {
        _io_service.run();
    }


    void Skaldi::TCPClient(std::string ip, unsigned short port)
    {
        _tcp_clt = new client::TCP(_io_service, ip, port);
    }

    void Skaldi::enableBroadcast()
    {
        this->_udp_srv->setBroadcasting(true);
//        this->_tcp_srv->setBroadcasting(true);
    }

    void Skaldi::disableBroadcast()
    {
        this->_udp_srv->setBroadcasting(false);
//        this->_tcp_srv->setBroadcasting(false);
    }

}