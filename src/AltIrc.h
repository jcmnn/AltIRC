#ifndef ALTIRC_ALTIRC_H
#define ALTIRC_ALTIRC_H

#include "IrcConnection.h"
#include "Logger.h"
#include "Plugin/PluginManager.h"
#include "ConnectionHandler.h"
#include <memory>
#include <list>

class AltIrc { // tolua_export
public:
    AltIrc(const AltIrc &copy) = delete;
    AltIrc();
    
    /* Runs the main AltIrc program */
    void run();
    
    /* Creates the global AltIrc instance */
    static void create();
    
    /* Deletes the global AltIrc instance */
    static void close();
    
    // tolua_begin
    inline static AltIrc &get();
    
    /* Returns the logger */
    inline Logger &logger();
    
    inline ConnectionHandler &connectionHandler();
    
    inline PluginManager &pluginManager();
    // tolua_end
    
private:
    static std::unique_ptr<AltIrc> altIrc_;
    Logger logger_;
    ConnectionHandler connectionHandler_;
    PluginManager pluginManager_;
}; // tolua_export



PluginManager &AltIrc::pluginManager() {
    return pluginManager_;
}

ConnectionHandler &AltIrc::connectionHandler() {
    return connectionHandler_;
}

AltIrc &AltIrc::get() {
    return *altIrc_.get();
}

Logger &AltIrc::logger() {
    return logger_;
}

#endif //ALTIRC_ALTIRC_H
