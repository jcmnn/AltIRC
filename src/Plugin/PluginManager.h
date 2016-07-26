#ifndef ALTIRC_PLUGINMANAGER_H
#define ALTIRC_PLUGINMANAGER_H

#include "../LuaState.h"
#include "CallbackHandler.h"

class PluginManager { // tolua_export
public:
    PluginManager();
    ~PluginManager();
    void initialize();
    
    // tolua_begin
    /* Returns the callback handler */
    inline CallbackHandler &callbackHandler();
    // tolua_end

    /* Reloads plugins */
    void reload();
private:
    lua_State *state_;
    CallbackHandler callbackHandler_;
}; // tolua_export

CallbackHandler &PluginManager::callbackHandler() {
    return callbackHandler_;
}

#endif //ALTIRC_PLUGINMANAGER_H
