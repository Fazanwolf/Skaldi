#ifndef SKALDI_ICLIENT_HPP
#define SKALDI_ICLIENT_HPP

#include <iostream>
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"
#include "boost/shared_ptr.hpp"
#include <thread>
#include <functional>

/**
 * @brief Skaldi namespace
 * @details Namespace for the Skaldi Client library
 */
namespace sk {

    /**
     * @brief Interface for a client
     */
    class IClient {
        public:
            /**
             * @brief Destructor
             * @details Virtual destructor to allow for polymorphism
             */
            virtual ~IClient() = default;
            /**
             * @brief Allow to send messages from the terminal
             */
            virtual void getInput() = 0;
            /**
             * @brief Send a message to the server
             * @param message Message to send
             */
            virtual void send(const std::string &message) = 0;
            /**
             * @brief Receive asynchronously messages from the server
             * @return Message received
             */
            virtual void receive() = 0;
            /**
             * @brief Enable or disable debugging mode
             * @details If debugging mode is enabled, the client will print the messages it sends and receives
             * @param debug
             * @return void
             */
            virtual void setDebugging(bool debug) = 0;
            /**
             * @brief Set the first connection
             * @details Set the first connection
             * @param fc
             */
            virtual void setFirstConnection(bool fc) = 0;

        protected:
            /**
             * @brief Handle the sending of a message
             * @param error Error code
             * @param message Message to send
             */
            virtual void handleSend(const boost::system::error_code &error, const std::string &message) = 0;
            /**
             * @brief Handle the reception of a message
             * @param error Error code
             * @param bytesTransferred Number of bytes transferred
             */
            virtual void handleReceive(const boost::system::error_code &error, std::size_t bytesTransferred) = 0;
    };

};

#endif //SKALDI_ICLIENT_HPP
