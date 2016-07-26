#ifndef ALTIRC_SOCKETADDRESS_H
#define ALTIRC_SOCKETADDRESS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <memory>

/* A simple wrapper that stores a socket address pointer */
class SocketAddress {
public:
    SocketAddress(sockaddr *address, socklen_t length);
    
    inline sockaddr *address() const;
    inline socklen_t length() const;
private:
    sockaddr *address_;
    socklen_t length_;
};

sockaddr* SocketAddress::address() const {
    return address_;
}

socklen_t SocketAddress::length() const {
    return length_;
}


#endif //ALTIRC_SOCKETADDRESS_H
