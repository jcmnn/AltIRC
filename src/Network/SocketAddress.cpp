#include "SocketAddress.h"

SocketAddress::SocketAddress(sockaddr *address, socklen_t length) : address_(address), length_(length) {

}
