#include <string.h>
#include <iostream>
#include "NetworkBuffer.h"

NetworkBuffer::NetworkBuffer() : pos_(0) {
    
}


const char *NetworkBuffer::data() {
    if (buffer_.empty()) {
        return "";
    }
    
    buffer_.reserve(buffer_.size() + 1);
    *(buffer_.end()) = '\0'; // Makes the buffer null-terminating
    
    return reinterpret_cast<const char*>(const_cast<const std::vector<unsigned char>*>(&buffer_)->data());
}

void NetworkBuffer::operator<<(const std::string &string) {
    buffer_.insert(buffer_.begin(), string.begin(), string.end());
}

NetworkBuffer::NetworkBuffer(const std::string &string) : buffer_(string.begin(), string.end()), pos_(0) {

}

bool NetworkBuffer::flushed() {
    return length() == pos();
}

NetworkBuffer::NetworkBuffer(NetworkBuffer &&nbuffer) {
    buffer_ = std::move(nbuffer.buffer_);
    pos_ = std::move(nbuffer.pos_);
}
