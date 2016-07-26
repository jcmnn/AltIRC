#include <algorithm>
#include "ProtocolHandler.h"
#include "IrcConnection.h"
#include "Logger.h"
#include "AltIrc.h"

ProtocolHandler::ProtocolHandler(IrcConnection *connection) : authed_(false), connection_(connection) {
    
}

std::array<unsigned char, 2> lDelimeter = {'\r', '\n'};

bool ProtocolHandler::read() {
    ssize_t bytes;
    while ((bytes = socket_.recv(readBuffer_, 8192)) >= 0);
    if (bytes == 0) {
        connection_->onDisconnect();
        return false;
    } else if (bytes == -1) {
        if (!socket_.wouldBlock()) {
            connection_->onDisconnect();
            return false;
        }
    }
    
    std::vector<unsigned char> &buf = readBuffer_.buffer();
    NetworkBuffer::BufferIterator ot = buf.begin();
    NetworkBuffer::BufferIterator it;
    while ((it = std::search(ot, buf.end(), lDelimeter.begin(), lDelimeter.end())) != buf.end()) {
        IrcMessage message(std::string(ot, it));
        handleMessage(message);
        ot = it + 2;
    }
    
    buf.erase(buf.begin(), ot);
    
    return true;
}


void ProtocolHandler::write() {
    if (!writeBuffer_.flushed()) {
        if (socket_.send(writeBuffer_) > 0) {
            std::vector<unsigned char> &buf = writeBuffer_.buffer();
            buf.erase(buf.begin(), buf.begin() + writeBuffer_.pos());
            writeBuffer_.setPos(0);
        }
    }
}

void ProtocolHandler::sendRaw(const std::string &string) {
    std::vector<unsigned char> &buf = writeBuffer_.buffer();
    buf.insert(buf.end(), string.begin(), string.end());
    buf.insert(buf.end(), lDelimeter.begin(), lDelimeter.end());

    write();
}

bool ProtocolHandler::connect() {
    socket_.connect(connection_->host(), connection_->port());
    socket_.setBlocking(false);

    if (!socket_.connected()) {
        LOGERR << "Could not connect to " << connection_->host() << std::endl;
        return false;
    }

    connection_->onConnect();
    sendNick(connection_->nick());
    sendUser(connection_->user(), connection_->realname(), 0);
    return true;
}

void ProtocolHandler::handleMessage(IrcMessage &message) {
    // Fire the "raw" event
    std::vector<CallbackArgPtr> args;
    args.push_back(argWrap(connection_, "IrcConnection"));
    if (message.prefix()) {
        args.push_back(argWrap<IrcPrefix>(*message.prefix(), "IrcPrefix"));
    } else {
        args.push_back(argWrap());
    }
    args.push_back(argWrap(message.command()));
    for (const std::string &string : message.params()) {
        args.push_back(argWrap(string));
    }
    AltIrc::get().pluginManager().callbackHandler().call("raw", args);
    
    if (message.command() == "PING") { // replies with PONG
        if (message.params().size() >= 0) {
            std::stringstream ss;
            ss << "PONG :" << message.params()[0];
            sendRaw(ss.str());
        }
    } else if (message.command() == "001") { // connected
        authed_ = true;
        connection_->onAuth();
        // Fire the auth event
        AltIrc::get().pluginManager().callbackHandler().call("auth", {argWrap(connection_, "IrcConnection")});
    } else if (message.command() == "PRIVMSG") {
        if (message.params().size() >= 2) {
            connection_->onMessage(message.prefix(), message.params()[0], message.params()[1]);

            std::vector<CallbackArgPtr> args;
            args.push_back(argWrap(connection_, "IrcConnection"));
            if (message.prefix()) {
                args.push_back(argWrap<IrcPrefix>(*message.prefix(), "IrcPrefix"));
            } else {
                args.push_back(argWrap());
            }
            args.push_back(argWrap(message.params()[0]));
            args.push_back(argWrap(message.params()[1]));
            AltIrc::get().pluginManager().callbackHandler().call("message", args);
        }
    }
}

void ProtocolHandler::sendNick(const std::string &nick) {
    ss_.str("");
    ss_ << "NICK :" << nick;
    sendRaw(ss_.str());
}

void ProtocolHandler::sendUser(const std::string &user, const std::string &realname, unsigned char mode) {
    ss_.str("");
    ss_ << "USER " << user << " " << (unsigned int)mode << " * :" << realname;
    sendRaw(ss_.str());
}

void ProtocolHandler::join(const std::string &channel) {
    ss_.str("");
    ss_ << "JOIN " << channel;
    sendRaw(ss_.str());
}

void ProtocolHandler::join(const std::string &channel, const std::string &password) {
    ss_.str("");
    ss_ << "JOIN " << channel << " " << password;
    sendRaw(ss_.str());
}

void ProtocolHandler::sendNotice(const std::string &target, const std::string &message) {
    ss_.str("");
    ss_ << "NOTICE " << target << " :" << message;
    sendRaw(ss_.str());
}

void ProtocolHandler::sendMessage(const std::string &target, const std::string &message) {
    ss_.str("");
    ss_ << "PRIVMSG " << target << " :" << message;
    sendRaw(ss_.str());
}

void ProtocolHandler::part(const std::string &channel) {
    ss_.str("");
    ss_ << "PART " << channel;
    sendRaw(ss_.str());
}

void ProtocolHandler::part(const std::string &channel, const std::string &message) {
    ss_.str("");
    ss_ << "PART " << channel << " :" << message;
    sendRaw(ss_.str());
}

ProtocolHandler::~ProtocolHandler() {
    if (authed_) {
        //LOGOUT << "Quiting " << connection_->host() << ":" << connection_->port() << std::endl;
        sendRaw("QUIT :Bye!");
    }
}
