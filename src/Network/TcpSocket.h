#ifndef ALTIRC_TCPCONNECTION_H
#define ALTIRC_TCPCONNECTION_H

#include <string>
#include <sstream>
#include "IPSocket.h"

// tolua_begin
class TcpSocket : public IPSocket {
public:
    TcpSocket();
    /* Tries to connect to hostname:port. If the connection fails,
       the socket is invalid */
    TcpSocket(const std::string &hostname, unsigned short port);
    
    /* Returns true if the socket is connected */
    inline bool connected();
    // tolua_end

    /* Overrides Socket::recv to check if the endpoint has disconnected */
    ssize_t recv(NetworkBuffer &buffer, size_t length) override;

    /* Overrides Socket::send to check if the endpoint has disconnected */
    ssize_t send(NetworkBuffer &buffer) override;

    /* Overrides IPSocket::connect to check if the endpoint has disconnected */
    bool connect(const std::string &hostname, unsigned short port);
private:
    bool connected_;
}; // tolua_export

bool TcpSocket::connected() {
    return connected_;
}

#endif //ALTIRC_TCPCONNECTION_H
