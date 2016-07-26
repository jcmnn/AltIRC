#include "PluginManager.h"
#include "../Logger.h"
#include "../AltIrc.h"
#include "Bind.h"

#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <fstream>

PluginManager::PluginManager() {
    state_ = luaL_newstate();
    if (state_ == nullptr) {
        LOGERR << "Plugin state could not be created" << std::endl;
    }
}

PluginManager::~PluginManager() {
    if (state_ != nullptr) {
        lua_close(state_);
    }
}

void PluginManager::initialize() {
    LuaState state(state_);
    callbackHandler_.initialize(state_);
    state.openLibs();
    tolua_binds_open(state_);
    
    DIR *dir = opendir("plugins");
    if (dir == NULL) {
        LOGERR << "Could not open plugins: " << strerror(errno) << std::endl;
    } else {
        std::ifstream file;
        dirent *d;
        std::stringstream ss;
        while ((d = readdir(dir)) != NULL) {
            if (d->d_type == DT_REG) {
                ss.str("");
                ss << "plugins/" << d->d_name;
                file.open(ss.str());
                if (!file.is_open()) {
                    LOGERR << "Could not open " << ss.str() << std::endl;
                    continue;
                }
                std::string data(std::istreambuf_iterator<char>(file), (std::istreambuf_iterator<char>()));
                file.close();
                
                int err = state.loadString(data.c_str());
                if (err != 0) {
                    switch (err) {
                        case LUA_ERRSYNTAX:
                            LOGERR << "Syntax error in " << ss.str() << ": " << state.tostring(-1) << std::endl;
                            state.pop(1);
                            break;
                        case LUA_ERRMEM:
                            LOGERR << "Memory allocation error while loading " << ss.str() << std::endl;
                            break;
                    }
                    continue;
                }
                
                err = state.pcall(0, 0);
                if (err != 0) {
                    switch(err) {
                        case LUA_ERRRUN:
                            LOGERR << "Runtime error in " << ss.str() << ": " << state.tostring(-1) << std::endl;
                            state.pop(1);
                            break;
                        case LUA_ERRMEM:
                            LOGERR << "Memory allocation error while running " << ss.str() << std::endl;
                            break;
                        default:
                            LOGERR << "Unknown error while running " << ss.str() << std::endl;
                            break;
                    }
                }
            }
        }
        
        closedir(dir);
    }
}

void PluginManager::reload() {
    lua_close(state_);
    state_ = luaL_newstate();
    initialize();
}
