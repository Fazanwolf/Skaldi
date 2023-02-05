#include "Skaldi.hpp"

namespace Skaldi {

    Skaldi::Skaldi()
    {
    }

    void Skaldi::createUDPServer(unsigned short port)
    {
        _udp_srv = new server::UDP(_io_service, port);
        _io_service.run();
    }

    void Skaldi::createTCPServer(unsigned short port)
    {
        _tcp_srv = new server::TCP(_io_service, port);
        _io_service.run();
    }

    void Skaldi::createUDPClient(const std::string &ip, const std::string &port)
    {
        _udp_clt = new client::UDP(_io_service, ip, port);
        _udp_clt->send("Hello it's a test for UDP server");
        _io_service.run();
    }

    void Skaldi::createTCPClient(std::string ip, unsigned short port)
    {
        _tcp_clt = new client::TCP(_io_service, ip, port);
        _io_service.run();
    }

}