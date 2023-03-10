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

    _cltUdp = nullptr;
    _srvUdp = nullptr;
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

    if (std::string("TCP") == type) {
        // do something for tcp server
    }

    if (std::string("UDP") == type) {
        this->_srvUdp = std::make_unique<sk::Server<sk::server::UDP>>(port);
        this->_srvUdp->setBroadcasting(true);
        this->_srvUdp->getInput();
        this->_srvUdp->run();
        return (0);
    }
    return this->invalidArgs();
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
    utilities::Transform::toUpper(type);

    if (std::string("TCP") == type) {
        // do something for tcp client
    }
    if ("UDP" == type) {
        this->_cltUdp = std::make_unique<sk::Client<sk::client::UDP>>(_av[3], _av[4]);
        this->_cltUdp->setDebugging(false);
        this->_cltUdp->receive();
        this->_cltUdp->connect("?");
        this->_cltUdp->run();
        this->_cltUdp->getInput();

        while (true) {
            std::string msg = this->_cltUdp->getBuffer();
            if (!msg.empty()) {
                std::cout << "Receive from buffer: " << msg << std::endl;
                if (msg == "all-exit") break;
                msg = "";
            }
        }
        this->_cltUdp->disconnect();
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
    if (_ac == 4 && std::string("server") == _av[1])
        return this->handleServer();
    if (_ac == 5 && std::string("client") == _av[1])
        return this->handleClient();
    return this->invalidArgs();
}
