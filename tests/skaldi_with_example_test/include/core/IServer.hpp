#ifndef SKALDI_ISERVER_HPP
#define SKALDI_ISERVER_HPP

#include <map>
#include <memory>
#include <iostream>
#include "boost/bind.hpp"
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
//          Todo: Search a way to use the correct endpoint
//            /**
//             * @brief Send a message to a client
//             * @details Send a message to a client
//             * @param message
//             * @param endpoint
//             * @return void
//             */
//            template <typename EndpointType>
//            virtual void send(const std::string &message, EndpointType &endpoint) = 0;
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

        protected:
            /**
             * @brief Broadcast a message to everyone
             * @details Broadcast a message to everyone
             * @param id
             * @param message
             * @return void
             */
            virtual void broadcast(const int &id, const std::string &message) = 0;
            /**
             * @brief Receive asynchronously messages from the clients
             * @details Receive asynchronously messages from the clients
             * @return void
             */
            virtual void receive() = 0;
            /**
             * @brief Handle the reception of a message
             * @details Handle the reception of a message
             * @param error
             * @param bytesTransferred
             * @return void
             */
            virtual void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred) = 0;
//           Todo: Search a way to use the correct endpoint
//            /**
//             * @brief Handle the sending of a message
//             * @details Handle the sending of a message
//             * @param error
//             * @param endpoint
//             * @param message
//             * @return void
//             */
//            virtual void handleSend(const boost::system::error_code &error, boost::asio::ip::udp::endpoint &endpoint, const std::string &message) = 0;
    };

}

#endif //SKALDI_ISERVER_HPP
