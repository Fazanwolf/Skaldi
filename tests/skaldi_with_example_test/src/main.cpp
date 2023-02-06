#include "ParserArgs.hpp"

int main(int ac, char **av)
{
    ParserArgs pa(ac, av);
    return pa.handler();
}