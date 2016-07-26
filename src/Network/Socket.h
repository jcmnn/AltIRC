#ifndef ALTIRC_SOCKET_H
#define ALTIRC_SOCKET_H

typedef int SOCKET; // tolua_export
#define BUFFER_SIZE 65535

#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include "SocketAddress.h"
#include "NetworkBuffer.h"

// tolua_begin
class Socket {
public:
    /* Initializes a socket with family, type, and protocol.
       If an error occurs, the socket is invalid (valid() returns false) and lastError()
       returns the error */
    Socket(int family, int type, int protocol);
    
    Socket();

    /* Closes the socket */
    ~Socket();

    /* Initializes a socket with family, type, and protocol.
       If an error occurs, returns false, the socket is invalid (valid() returns false),
       and lastError() returns the error */
    bool initialize(int family, int type, int protocol);

    /* Received data from the socket. Returns the number of bytes read.
       Returns -1 if an error occurred. If the end-of-file is reached,
       returns 0 and eof() returns true. Returns 0 if the socket reads nothing
       due to nonblocking */
    virtual ssize_t recv(NetworkBuffer &buffer, size_t length);
    

    /* Sends data through the socket. Returns the number of bytes read.
       Returns -1 if an error occurred. If the end-of-file is reached,
       returns 0. Moves the position of the buffer
       to the next byte to be sent. Returns 0 if the socket reads nothing
       due to nonblocking */
    virtual ssize_t send(NetworkBuffer &buffer);
    
    /* Gets the last error code */
    inline int lastErrorCode();
    
    /* Returns true if the last recv or send operation was canceled due to nonblocking */
    bool wouldBlock();
    
    /* Attempts to connect to an address. If an error occurs, returns false */
    bool connect(const SocketAddress &address);

    /* Returns the raw socket handler */
    inline SOCKET raw();
    
    /* Sets the socket to blocking or nonblocking */
    bool setBlocking(bool blocking);
    
    /* Returns the last error */
    inline std::string lastError();
    
    /* Returns true if the Socket is initialized */
    inline bool valid();
    
    /* Closes the socket */
    inline void close();
    // tolua_end

    /* Socket should not be copied due to the destructor closing the handle */
    Socket(const Socket &copy) = delete;
protected:
    std::string lastError_;
    int lastErrorCode_;
    SOCKET socket_;
}; // tolua_export



int Socket::lastErrorCode() {
    return lastErrorCode_;
}

void Socket::close() {
    ::close(socket_);
    socket_ = -1;
}

bool Socket::valid() {
    return socket_ != -1;
}

SOCKET Socket::raw() {
    return socket_;
}

std::string Socket::lastError() {
    return lastError_;
}

#endif //ALTIRC_SOCKET_H
