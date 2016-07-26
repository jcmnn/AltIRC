#ifndef ALTIRC_CONNECTIONHANDLER_H
#define ALTIRC_CONNECTIONHANDLER_H


#include "IrcConnection.h"
#include <list>

typedef std::unique_ptr<IrcConnection> ConnectionPtr;

class ConnectionHandler { // tolua_export
public:
    ConnectionHandler();

    /* Called internally by IrcConnection to add a new connection */
    void addConnection(IrcConnection *connection);

    /* Called internally by IrcConnection when the socket closes */
    void removeConnection(Socket &socket);
    
    /* Creates a new connection */
    IrcConnection *newConnection(const std::string &host, unsigned short port, const std::string &nick, const std::string &user, const std::string &realname); // tolua_export
    
    /* Called internally by AltIrc to poll sockets */
    void run();
    
    /* Deletes copy constructor */
    ConnectionHandler(const ConnectionHandler &copy) = delete;
private:
    std::list<ConnectionPtr> connections_;
    int efd_; // epoll interface file descriptor
}; // tolua_export


#endif //ALTIRC_CONNECTIONHANDLER_H
