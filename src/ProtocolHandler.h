#ifndef ALTIRC_PROTOCOLHANDLER_H
#define ALTIRC_PROTOCOLHANDLER_H

class IrcConnection;

#include "Network/TcpSocket.h"
#include "IrcMessage.h"

class ProtocolHandler { // tolua_export
public:
    ProtocolHandler(IrcConnection *connection);
    
    /* read() should be called when data is ready to be received.
       Returns true if the socket closed */
    bool read();
    
    /* Establishes a connection to the server. Returns false if the socket did not connect */
    bool connect();
    
    /* write() should be called when data is ready to be sent */
    void write();
    
    // tolua_begin
    /* Returns the internal TcpSocket */
    inline TcpSocket &socket();
    
    /* Queues a message to be sent */
    void sendRaw(const std::string &str);
    
    /* Sends NICK message */
    void sendNick(const std::string &nick);
    
    /* Sends USER message */
    void sendUser(const std::string &user, const std::string &realname, unsigned char mode);
    
    /* Attempts to join a channel */
    void join(const std::string &channel);

    /* Attempts to join a channel with a password */
    void join(const std::string &channel, const std::string &password);

    /* Attempts to part from a channel */
    void part(const std::string &channel);

    /* Attempts to part from a channel with a message */
    void part(const std::string &channel, const std::string &message);
    
    /* Sends a notice to target */
    void sendNotice(const std::string &target, const std::string &message);

    /* Sends a message to target */
    void sendMessage(const std::string &target, const std::string &message);
    // tolua_end
    
    ~ProtocolHandler();
private:
    TcpSocket socket_;
    IrcConnection *connection_;
    NetworkBuffer readBuffer_;
    NetworkBuffer writeBuffer_;
    
    bool authed_;
    
    std::stringstream ss_;
    
    void handleMessage(IrcMessage &message);
}; // tolua_export



TcpSocket &ProtocolHandler::socket() {
    return socket_;
}


#endif //ALTIRC_PROTOCOLHANDLER_H
