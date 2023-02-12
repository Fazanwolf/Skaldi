#ifndef SKALDI_TYPE_HPP
#define SKALDI_TYPE_HPP

#include "core/client_type/TCP.hpp"
#include "core/client_type/UDP.hpp"
#include "core/server_type/TCP.hpp"
#include "core/server_type/UDP.hpp"

namespace sk::type {

    enum InternetProtocol {
        TCP,
        UDP
    };

    enum Client {
        TCP = sk::client::TCP,
        UDP = sk::client::UDP
    };

    enum Server {
        TCP = sk::server::TCP,
        UDP = sk::server::UDP
    };

}

#endif //SKALDI_TYPE_HPP
