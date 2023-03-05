#ifndef SKALDI_ISERVER_HPP
#define SKALDI_ISERVER_HPP

#include <map>
#include <memory>
#include <iostream>
#include "boost/bind/bind.hpp"
#include "boost/asio.hpp"
#include "boost/array.hpp"
#include "boost/shared_ptr.hpp"

namespace sk {

    class IServer {
        public:
            /**
             * @brief Destructor
             * @details Virtual destructor to allow for polymorphism
             */
            virtual ~IServer() = default;
            /**
             * @brief Send a message to everyone
             * @details Send a message to everyone
             * @param message
             * @return void
             */
            virtual void sendToEveryone(const std::string &message) = 0;
            /**
             * @brief Allow to send messages from the terminal
             * @details Allow to send messages from the terminal
             * @return void
             */
            virtual void getInput() = 0;
            /**
             * @brief Enable or disable broadcasting
             * @details Enable or disable broadcasting
             * @param able
             * @return void
             */
            virtual void setBroadcasting(bool able) = 0;

            /**
             * @brief Receive asynchronously messages from the clients
             * @details Receive asynchronously messages from the clients
             * @return void
             */
            virtual void receive() = 0;
    };

}

#endif //SKALDI_ISERVER_HPP
