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
    this->_g = new Skaldi::Skaldi();
}

/**
 * Destructor of ParserArgs
 */
ParserArgs::~ParserArgs()
{
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

    if (utilities::Check::strIsEqual("tcp", type)) {
        std::cout << "SERVER TCP: Todo" << std::endl;
    } else if (utilities::Check::strIsEqual("udp", type)) {
        std::cout << "SERVER UDP: Todo" << std::endl;
    }
    return this->invalidArgs();
}

/**
 * HandleClient function
 * Handle the client side arguments
 * @return int
 */
void ParserArgs::handleClient()
{
    if (!utilities::Check::isIp(_av[3]) || !utilities::Check::isPort(_av[4]))
        return this->invalidArgs();

    std::string type = std::string(_av[2]);
    utilities::Transform::toLower(type);

    if (utilities::Check::strIsEqual("tcp", type)) {
        std::cout << "CLIENT TCP: Todo" << std::endl;
    } else if (utilities::Check::strIsEqual("udp", type)) {
        std::cout << "CLIENT UDP: Todo" << std::endl;
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
    else if (utilities::Check::isAlias(_av[1], "--version", "-v"))
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
    else if (_ac == 4 && utilities::Check::strIsEqual("server", _av[1]))
        return this->handleServer();
    else if (_ac == 5 && && utilities::Check::strIsEqual("client", _av[1]))
        return this->handleClient();
    return this->invalidArgs();
}
