#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "Socket.h"

Socket::Socket(int family, int type, int protocol) {
    socket_ = socket(family, type, protocol);
    if (socket_ == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
    }
}

// TODO: Fix this shit
ssize_t Socket::recv(NetworkBuffer &buffer, size_t length) {
    std::vector<unsigned char> &buf = buffer.buffer();
    
    char b[length];
    
    ssize_t bytes = ::recv(socket_, b, length, 0);
    if (bytes == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
        return -1;
    } else if (bytes > 0) {
        buf.insert(buf.end(), b, b + bytes);
    }

    return bytes;
}

ssize_t Socket::send(NetworkBuffer &buffer) {
    std::vector<unsigned char> &buf = buffer.buffer();
    ssize_t bytes = ::send(socket_, buf.data() + buffer.pos(), buffer.remaining(), 0);
    if (bytes == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
    } else if (bytes > 0) {
        buffer.setPos(buffer.pos() + bytes);
    }

    return bytes;
}

Socket::Socket() : socket_(-1) {

}

bool Socket::setBlocking(bool blocking) { 
    int flags = fcntl(socket_, F_GETFL);
    if (flags == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
        return false;
    }
    
    if (blocking) {
        flags &= ~O_NONBLOCK;
    } else {
        flags |= O_NONBLOCK;
    }
    
    if (fcntl(socket_, F_SETFL, flags) == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
        return false;
    }
    
    return true;
}

bool Socket::initialize(int family, int type, int protocol) {
    socket_ = socket(family, type, protocol);
    if (socket_ == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
        return false;
    }
    return true;
}

bool Socket::connect(const SocketAddress &address) {
    if (::connect(socket_, address.address(), address.length()) == -1) {
        lastErrorCode_ = errno;
        lastError_ = strerror(errno);
        return false;
    }
    return true;
}

bool Socket::wouldBlock() {
    return lastErrorCode_ == EAGAIN || lastErrorCode_ == EWOULDBLOCK;
}

Socket::~Socket() {
    if (socket_ != -1) {
        ::close(socket_);
    }
}
