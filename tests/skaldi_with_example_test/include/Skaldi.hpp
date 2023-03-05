#ifndef SKALDI_HPP
#define SKALDI_HPP

#include <spdlog/spdlog.h>
#include "core/server/Server.hpp"
#include "core/client/Client.hpp"
#include "protocol/BinaryManipulation.hpp"

//enum IP {
//    TCP,
//    UDP
//};

//namespace sk {
//
//    /**
//     * @brief Class Skaldi that will be used to create a client or a server
//     */
//    template <typename T>
//    class Skaldi {
//    public:
//
//        /**
//         * @brief Constructor of Skaldi
//         * @details Constructor of Skaldi that will create a server
//         * @param port
//         */
//        explicit Skaldi(unsigned short port)
//        {
////            if (T == IP::TCP)
//            if (std::is_same<T, sk::server::TCP>::value)
//                server = new Server<sk::server::TCP>(_ioContext, port);
//            if (std::is_same<T, sk::server::UDP>::value)
//                server = reinterpret_cast<Server <TCP> *>(new Server<sk::server::UDP>(_ioContext, port));
////            if (typeid(T) == typeid(sk::server::TCP))
////                server = new Server<sk::server::TCP>(_ioContext, port);
////            if (T == IP::UDP)
////            if (typeid(T) == typeid(sk::server::UDP))
////                server = new Server<sk::server::UDP>(_ioContext, port);
//        }
//
//        /**
//         * @brief Constructor of Skaldi
//         * @details Constructor of Skaldi that will create a client
//         * @param host
//         * @param port
//         */
//        explicit Skaldi(const std::string &host, const std::string &port)
//        {
////            if (T == IP::TCP)
//            if (std::is_same<T, sk::client::TCP>::value)
//                client = new Client<sk::client::TCP>(_ioContext, host, port);
//            if (std::is_same<T, sk::client::UDP>::value)
//                client = new Client<sk::client::UDP>(_ioContext, host, port);
////            if (typeid(T) == typeid(sk::client::TCP))
////                client = new Client<sk::client::TCP>(_ioContext, host, port);
////            if (T == IP::UDP)
////            if (typeid(T) == typeid(sk::client::UDP))
////                client = new Client<sk::client::UDP>(_ioContext, host, port);
//        }
//
//        /**
//         * @brief Destructor of Skaldi
//         * @details Destructor of Skaldi that will delete the client or the server
//         */
//        ~Skaldi() = default;
//
//        boost::asio::io_context &getIoContext()
//        {
//            return _ioContext;
//        }
//
//        void run()
//        {
//            _ioContext.run();
//        }
//
//        void runOne()
//        {
//            _ioContext.run_one();
//        }
//
//        void pollOne()
//        {
//            _ioContext.poll_one();
//        }
//
//        void poll()
//        {
//            _ioContext.poll();
//        }
//
//        Client<T> *client;
//        Server <UDP> *server;
//
//    private:
//        boost::asio::io_context _ioContext;
//    };
//};

#endif //SKALDI_HPP