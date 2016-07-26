#include "IrcMessage.h"

#include <algorithm>
#include <sstream>

IrcMessage::IrcMessage(std::string message) {
    if (message.empty()) {
        valid_ = false;
        return;
    }
    
    std::stringstream ss(message);
    
    if (ss.peek() == ':') {
        std::string prefix;
        ss >> prefix;
        
        // Parse the prefix
        prefix_ = PrefixPtr(new IrcPrefix(prefix.begin() + 1, prefix.end()));
    }
    
    ss >> command_;
    std::string param;
    while (ss) {
        ss.seekg(1, std::ios::cur);
        if (ss.peek() == ':') {
            ss.seekg(1, std::ios::cur);
            params_.push_back(std::string(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>()));
            break;
        }
        ss >> param;
        params_.push_back(param);
    }

    valid_ = true;
}

template<class InputIterator>
IrcPrefix::IrcPrefix(InputIterator start, InputIterator end) {
    if (start == end) {
        return;
    }
    InputIterator nStart = std::find(start, end, '@');
    if (nStart != end) {
        host_.append(nStart + 1, end);
        InputIterator uStart = std::find(start, nStart, '!');
        if (uStart != nStart) {
            user_.append(uStart + 1, nStart);
            nStart = uStart;
        }
    }

    name_.append(start, nStart);
}
