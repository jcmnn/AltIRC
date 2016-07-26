#include <netinet/in.h>
#include "TcpSocket.h"

TcpSocket::TcpSocket(const std::string &hostname, unsigned short port) : IPSocket(SOCK_STREAM, IPPROTO_TCP, hostname, port) {
    connected_ = valid();
}

ssize_t TcpSocket::recv(NetworkBuffer &buffer, size_t length) {
    ssize_t bytes = Socket::recv(buffer, length);
    if (bytes == 0 || (bytes == -1 && !wouldBlock())) {
        connected_ = false;
    }
    return bytes;
}

ssize_t TcpSocket::send(NetworkBuffer &buffer) {
    ssize_t bytes = Socket::send(buffer);
    //if (bytes == 0 || (bytes == -1 && !wouldBlock())) {
        //connected_ = false;
    //}
    return bytes;
}

bool TcpSocket::connect(const std::string &hostname, unsigned short port) {
    connected_ = IPSocket::connect(SOCK_STREAM, IPPROTO_TCP, hostname, port);
    return connected_;
}

TcpSocket::TcpSocket() : connected_(false) {

}
