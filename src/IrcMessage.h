#ifndef ALTIRC_PROTOCOLPARSER_H
#define ALTIRC_PROTOCOLPARSER_H

#include <string>
#include <vector>
#include <memory>

#include "Network/NetworkBuffer.h"

class IrcPrefix { // tolua_export
public:
    /* Parses the prefix */
    template<class InputIterator>
    IrcPrefix(InputIterator start, InputIterator end);

    /* Returns true if the message is formatted correctly */
    inline bool valid();
    
    // tolua_begin
    /* Returns the parsed nickname/servername */
    inline std::string name() const;
    
    /* Returns the parsed username */
    inline std::string user() const;
    
    /* Returns the parsed hostname */
    inline std::string host()  const;
    // tolua_end
private:
    std::string name_;
    std::string user_;
    std::string host_;
    
    bool valid_;
}; // tolua_export



bool IrcPrefix::valid() {
    return valid_;
}

std::string IrcPrefix::name() const {
    return name_;
}

std::string IrcPrefix::user() const {
    return user_;
}

std::string IrcPrefix::host() const {
    return host_;
}

typedef std::shared_ptr<IrcPrefix> PrefixPtr;

class IrcMessage {
public:
    IrcMessage(std::string message);
    
    /* Returns true if the message is formatted correctly */
    inline bool valid();
    
    inline PrefixPtr prefix();
    inline std::string &command();
    inline std::vector<std::string> &params();
private:
    PrefixPtr prefix_;
    std::string command_;
    std::vector<std::string> params_;
    
    bool valid_;
};

std::string &IrcMessage::command() {
    return command_;
}

PrefixPtr IrcMessage::prefix() {
    return prefix_;
}

std::vector<std::string> &IrcMessage::params() {
    return params_;
}

bool IrcMessage::valid() {
    return valid_;
}

#endif //ALTIRC_PROTOCOLPARSER_H
