#include "ParserArgs.hpp"

/**
 * Constructor of ParserArgs
 * Initialize the number of arguments & the list of arguments
 * @param ac number of arguments
 * @param av list of arguments
 */
ParserArgs::ParserArgs(int ac, char **av)
{
    this->_ac = ac;
    this->_av = av;

    this->udp = nullptr;
    this->tcp = nullptr;
    this->clt_tcp = nullptr;
    this.udp = nullptr;
    this->srv_tcp = nullptr;
    this->srv_udp = nullptr;
}

/**
 * Destructor of ParserArgs
 */
ParserArgs::~ParserArgs()
{
    if (this->udp != nullptr)
        delete this->udp;
    if (this->tcp != nullptr)
        delete this->tcp;
}

/**
 * Helper function
 * Display the helper of the program
 * @return int
 */
int ParserArgs::helper()
{
    std::cout << HELPER << std::endl;
    return (0);
}

/**
 * Version function
 * Display the version of the program
 * @return int
 */
int ParserArgs::version()
{
    std::cout << VERSION << std::endl;
    return (0);
}

/**
* InvalidArgs function
* Display on the error output the error message
* @return int
*/
int ParserArgs::invalidArgs()
{
    std::cerr << INVALID_ARGS << std::endl;
    return (84);
}

/**
 * HandleServer function
 * Handle the server side arguments
 * @return int
 */
int ParserArgs::handleServer()
{
    if (!utilities::Check::isPort(std::string(_av[3])))
        return this->invalidArgs();

    std::string type = std::string(_av[2]);
    utilities::Transform::toUpper(type);
    const unsigned short port = static_cast<unsigned short>(std::stoi(_av[3]));

    if (utilities::Check::strIsEqual("tcp", type)) {
        this.tcp = sk::Skaldi<InternetProtocol::TCP>(port);
        this.tcp.server.setBroadcasting(true);
        this.tcp.server.getInput();
        this.tcp.run();
        return (0);
    }
    if (utilities::Check::strIsEqual("udp", type)) {
        this.srv_udp = sk::Skaldi<InternetProtocol::UDP>(port);
        this.srv_udp.server.setBroadcasting(true);
        this.srv_udp.server.getInput();
        this.srv_udp.run();
        return (0);
    }
    return this->invalidArgs();
}

void test(std::string uwu)
{
    std::cout << "test" << uwu << std::endl;
}

/**
 * HandleClient function
 * Handle the client side arguments
 * @return int
 */
int ParserArgs::handleClient()
{
    if (!utilities::Check::isIp(_av[3]) || !utilities::Check::isPort(_av[4]))
        return this->invalidArgs();

    std::string type = std::string(_av[2]);
    utilities::Transform::toLower(type);

    if (utilities::Check::strIsEqual("tcp", type)) {
        this->clt_tcp = new sk::Skaldi<sk::client::TCP, sk::server::TCP>(_av[3], _av[4]);
        this->clt_tcp->client->getInput();
        this->clt_tcp->run();
        return (0);
    }
    if (utilities::Check::strIsEqual("udp", type)) {
        this.udp = new sk::Skaldi<sk::client::UDP, sk::server::UDP>(_av[3], _av[4]);
        this.udp->client->setDebugging(false);
        this.udp->client->setFirstConnection(true);
        this.udp->client->firstConnection("?");

        std::thread t([&]() {
            while (true) {
                std::string msg = this.udp->client->getBuffer();
                if (!msg.empty()) std::cout << "Receive: " << msg << std::endl;
                /* Use that code when you want to send data every X seconds */
//                boost::asio::io_context io;
//                boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
//                t.async_wait([&](const boost::system::error_code &ec) {
//                    if (ec) {
//                        std::cout << "error: " << ec.message() << std::endl;
//                    } else {
//                        this.udp->client->send("test");
//                    }
//                });
//                io.run();
            }
        });
        t.detach();
//        this.udp->client->getInput();
        this.udp->run();
        return (0);
    }
    return this->invalidArgs();
}

/**
 * BasicArgs function
 * Handle the basic arguments of the program (help, version)
 * @return int
 */
int ParserArgs::basicArgs()
{
    if (utilities::Check::isAlias(_av[1], "--help", "-h"))
        return this->helper();
    if (utilities::Check::isAlias(_av[1], "--version", "-v"))
        return this->version();
    return this->invalidArgs();
}

/**
 * Handler function
 * Handle the arguments of the program
 * @return int
 */
int ParserArgs::handler()
{
    if (_ac == 2)
        return this->basicArgs();
    if (_ac == 4 && utilities::Check::strIsEqual("server", _av[1]))
        return this->handleServer();
    if (_ac == 5 && utilities::Check::strIsEqual("client", _av[1]))
        return this->handleClient();
    return this->invalidArgs();
}
