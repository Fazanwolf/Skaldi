#include "ParserArgs.hpp"

/**
 * @brief Main to test BinaryManipulation
 * @return
 */
//int main()
//{
//    PlayerProtocol pp;
//
//    pp.printPacket();
//    pp.setPlayerId(PlayerProtocol::PlayerIDEnum::PLAYER2);
//    pp.printPacket();
//    pp.setPlayerMove(PlayerProtocol::PlayerActionEnum::UP, true);
//    pp.printPacket();
//    pp.setPlayerShoot(true);
//    pp.printPacket();
//}

/**
 * @brief Main to test ParserArgs
 * @param ac
 * @param av
 * @return
 */
int main(int ac, char **av)
{
    ParserArgs pa(ac, av);
    return pa.handler();
}