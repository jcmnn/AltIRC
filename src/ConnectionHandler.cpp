#include "ConnectionHandler.h"
#include "Logger.h"
#include "AltIrc.h"

#include <sys/epoll.h>
#include <string.h>

void ConnectionHandler::run() {
    if (efd_ == -1) {
        return;
    }

    epoll_event events[16];
    
    int ecount;
    while (true) {
        ecount = epoll_wait(efd_, events, 16, -1);
        if (ecount == -1) {
            LOGERR << "epoll_wait failed: " << strerror(errno) << std::endl;
            return;
        }
        
        for (int i = 0; i < ecount; i++) {
            ProtocolHandler &handler = reinterpret_cast<IrcConnection*>(events[i].data.ptr)->protocolHandler();
            if (events[i].events & EPOLLIN) {
                handler.read();
            }
            if (events[i].events & EPOLLOUT) {
                handler.write();
            }
        }
    }
}

void ConnectionHandler::addConnection(IrcConnection *connection) {
    epoll_event ev;
    ev.data.ptr = reinterpret_cast<void*>(connection);
    ev.events = EPOLLIN | EPOLLOUT;

    epoll_ctl(efd_, EPOLL_CTL_ADD, connection->protocolHandler().socket().raw(), &ev);
}

void ConnectionHandler::removeConnection(Socket &socket) {
    epoll_ctl(efd_, EPOLL_CTL_DEL, socket.raw(), NULL);
}

ConnectionHandler::ConnectionHandler() {
    if ((efd_ = epoll_create(1)) == -1) {
        LOGERR << "Could not create epoll interface: " << strerror(errno) << std::endl;
        return;
    }
}

IrcConnection *ConnectionHandler::newConnection(const std::string &host, unsigned short port, const std::string &nick, const std::string &user, const std::string &realname) {
    IrcConnection *conn = new IrcConnection(host, port, nick, user, realname);
    connections_.push_back(ConnectionPtr(conn));
    
    return conn;
}
