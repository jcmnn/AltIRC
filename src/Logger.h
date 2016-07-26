#ifndef ALTIRC_LOGGER_H
#define ALTIRC_LOGGER_H

#define LOGOUT AltIrc::get().logger().sout
#define LOGERR AltIrc::get().logger().serr

#include <iostream>

class Logger { // tolua_export
public:
    Logger();
    std::ostream &sout;
    std::ostream &serr;
    
    // tolua_begin
    void out(const char *message);
    void err(const char *message);
};
// tolua_end


#endif //ALTIRC_LOGGER_H
