#include "IrcConnection.h"
#include "AltIrc.h"

IrcConnection::IrcConnection(const std::string &host, unsigned short port, const std::string &nick, const std::string &user, const std::string &realname) : host_(host), port_(port), nick_(nick), user_(user), realname_(realname), protocolHandler_(this) {
    protocolHandler_.connect();
}

void IrcConnection::onConnect() {
    AltIrc::get().connectionHandler().addConnection(this);
}

void IrcConnection::onDisconnect() {
    AltIrc::get().connectionHandler().removeConnection(protocolHandler_.socket());
}

void IrcConnection::onAuth() {
    LOGOUT << "Connected to " << host_ << ":" << port_ << std::endl;
}

void IrcConnection::onNick(const PrefixPtr &prefix, const std::string &newNick) {
    if (prefix->name() == nick_) {
        nick_ = newNick;
    }
}

void IrcConnection::onMessage(const PrefixPtr &prefix, const std::string &target, const std::string &message) {

}
