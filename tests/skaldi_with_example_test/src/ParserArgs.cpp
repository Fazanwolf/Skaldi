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
    this->clt_udp = nullptr;
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
    if (this->clt_tcp != nullptr)
        delete this->clt_tcp;
    if (this->clt_udp != nullptr)
        delete this->clt_udp;
    if (this->srv_tcp != nullptr)
        delete this->srv_tcp;
    if (this->srv_udp != nullptr)
        delete this->srv_udp;
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
    utilities::Transform::toLower(type);
    const unsigned short port = static_cast<unsigned short>(std::stoi(_av[3]));

    if (utilities::Check::strIsEqual("tcp", type)) {
        this->srv_tcp = new sk::Skaldi<sk::client::TCP, sk::server::TCP>(port);
        this->srv_tcp->server->setBroadcasting(true);
        this->srv_tcp->server->getInput();
        this->srv_tcp->run();
        return (0);
    }
    if (utilities::Check::strIsEqual("udp", type)) {
        this->srv_udp = new sk::Skaldi<sk::client::UDP, sk::server::UDP>(port);
        this->srv_udp->server->setBroadcasting(true);
        this->srv_udp->server->getInput();
        this->srv_udp->run();
        return (0);
    }
    return this->invalidArgs();
}

void test(int i)
{
    std::cout << "test" << i << std::endl;
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
        this->clt_udp = new sk::Skaldi<sk::client::UDP, sk::server::UDP>(_av[3], _av[4]);
        this->clt_udp->client->setDebugging(true);
        this->clt_udp->client->setFirstConnection(true);
        this->clt_udp->client->firstConnection<void, ...int>(test, 1);/
        this->clt_udp->client->receive();
        this->clt_udp->client->getInput();
        this->clt_udp->run();
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
