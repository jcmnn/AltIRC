#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "IPSocket.h"

IPSocket::IPSocket(int type, int protocol, const std::string &hostname, unsigned short port) {
    connect(type, protocol, hostname, port);
}

bool IPSocket::connect(int type, int protocol, const std::string &hostname, unsigned short port) {
    addrinfo hints;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = type;
    hints.ai_protocol = protocol;
    hints.ai_flags = AI_V4MAPPED | AI_ADDRCONFIG | AI_NUMERICSERV;
    
    port = htons(port);

    addrinfo *faddr;
    int err;
    if ((err = getaddrinfo(hostname.c_str(), NULL, &hints, &faddr)) != 0) {
        lastError_ = gai_strerror(err);
        return false;
    }
    addrinfo *addr = faddr;

    do {
        if (!initialize(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) {
            continue;
        }
        
        switch (addr->ai_family) {
            case AF_INET:
                reinterpret_cast<sockaddr_in*>(addr->ai_addr)->sin_port = port;
                break;
            case AF_INET6:
                reinterpret_cast<sockaddr_in6*>(addr->ai_addr)->sin6_port = port;
                break;
        }
        
        if (Socket::connect(SocketAddress(addr->ai_addr, addr->ai_addrlen))) {
            break;
        }
        close();
    } while ((addr = addr->ai_next) != NULL);

    if (addr == NULL) {
        // Connection failed, bail out. lastError is set from the call to initialize() or connect()
        freeaddrinfo(addr);
        return false;
    }

    freeaddrinfo(addr);
    return true;
}

IPSocket::IPSocket() {

}
