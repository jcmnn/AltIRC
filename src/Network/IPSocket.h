#ifndef ALTIRC_IPSOCKET_H
#define ALTIRC_IPSOCKET_H

#include "Socket.h"

// tolua_begin
class IPSocket : public Socket {
public:
    IPSocket();
    /* Tries to connect to hostname:port. If the connection fails,
       the socket is invalid and lastError() returns the error */
    IPSocket(int type, int protocol, const std::string &hostname, unsigned short port);

    /* Tries to connect to hostname:port. If the connection fails,
       returns false and lastError() returns the error */
    virtual bool connect(int type, int protocol, const std::string &hostname, unsigned short port);
}; 
// tolua_end

#endif //ALTIRC_IPSOCKET_H
