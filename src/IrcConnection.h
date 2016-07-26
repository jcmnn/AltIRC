#ifndef ALTIRC_IRCCONNECTION_H
#define ALTIRC_IRCCONNECTION_H

#include "Network/TcpSocket.h"
#include "ProtocolHandler.h"

// tolua_begin
class IrcConnection {
public:
    /* Attempts to connect to host:port */
    IrcConnection(const std::string &host, unsigned short port, const std::string &nick, const std::string &user, const std::string &realname);
    
    inline ProtocolHandler &protocolHandler();
    
    /* Returns the currently used nickname */
    inline std::string nick();
    
    /* Returns the currently used username */
    inline std::string user();
    
    /* Returns the currently used realname */
    inline std::string realname();
    
    /* Returns the remote hostname */
    inline std::string host();
    
    /* Returns the remote port */
    inline unsigned short port();
    // tolua_end
    
    /* Called by ProtocolHandler when the socket disconnects */
    void onDisconnect();
    
    /* Called by ProtocolHandler when the socket connects */
    void onConnect();
    
    /* Called by ProtocolHandler when we are authorized */
    void onAuth();
    
    /* Called by ProtocolHandler when a nickname changes */
    void onNick(const PrefixPtr &prefix, const std::string &newNick);
    
    /* Called by ProtocolHandler when a message is received */
    void onMessage(const PrefixPtr &prefix, const std::string &target, const std::string &message);
    
    IrcConnection(const IrcConnection &copy) = delete;
private:
    ProtocolHandler protocolHandler_;
    std::string nick_;
    std::string user_;
    std::string realname_;
    
    
    std::string host_;
    unsigned short port_;
}; // tolua_export



std::string IrcConnection::host() {
    return host_;
}

unsigned short IrcConnection::port() {
    return port_;
}

std::string IrcConnection::realname() {
    return realname_;
}

std::string IrcConnection::nick() {
    return nick_;
}

std::string IrcConnection::user() {
    return user_;
}

ProtocolHandler &IrcConnection::protocolHandler() {
    return protocolHandler_;
}

#endif //ALTIRC_IRCCONNECTION_H
