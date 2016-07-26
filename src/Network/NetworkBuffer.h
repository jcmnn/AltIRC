#ifndef ALTIRC_NETWORKBUFFER_H
#define ALTIRC_NETWORKBUFFER_H

#include <vector>
#include <sys/types.h>
#include <string>

// tolua_begin
class NetworkBuffer { 
public:
    NetworkBuffer();

    /* Initializes the buffer with a string */
    NetworkBuffer(const std::string &data);
    
    /* Returns a null-terminating string of the data.
      This method should ONLY be used for Lua. Use buffer().data() instead. */
    const char *data();

    /* Returns the position of the buffer */
    inline size_t pos();

    /* Sets the position of the buffer */
    inline void setPos(size_t pos);

    /* Returns the length of the buffer */
    inline size_t length();

    /* Returns true if the buffer has been fully flushed (the length is equal to the position) */
    bool flushed();

    /* Returns the length of the buffer - the position */
    inline size_t remaining();
    // tolua_end

    /* Returns a reference to the internal buffer */
    inline std::vector<unsigned char> &buffer();
    
    /* Stream operator that appends a string to the buffer */
    void operator<<(const std::string &string);

    /* Initializes the buffer with move semantics */
    NetworkBuffer(NetworkBuffer &&nbuffer);
    
    typedef std::vector<unsigned char>::iterator BufferIterator;
private:
    std::vector<unsigned char> buffer_;
    size_t pos_;
}; // tolua_export



size_t NetworkBuffer::remaining() {
    return length() - pos_;
}

size_t NetworkBuffer::length() {
    return buffer_.size();
}

void NetworkBuffer::setPos(size_t pos) {
    pos_ = pos;
}

size_t NetworkBuffer::pos() {
    return pos_;
}

std::vector<unsigned char> &NetworkBuffer::buffer() {
    return buffer_;
}
#endif //ALTIRC_NETWORKBUFFER_H
