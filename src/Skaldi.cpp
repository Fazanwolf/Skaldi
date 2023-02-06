#include "Skaldi.hpp"

namespace Skaldi {

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

    void Skaldi::getInputUDPClient()
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

}