#include "CallbackHandler.h"
#include "../Logger.h"
#include "../AltIrc.h"

CallbackHandler::CallbackHandler() {

}

void CallbackHandler::initialize(lua_State *L) {
    state_ = L;

    LuaState state(L);
    state.push(this);
    state.createTable();
    state.setTable(LUA_REGISTRYINDEX);
}

bool CallbackHandler::registerEvent(lua_State *L, const std::string &event, const std::string &id, lua_Object func) {
    LuaState state(L);
    if (!state.isFunction(func)) {
        return false;
    }
    
    state.push(this);
    state.getTable(LUA_REGISTRYINDEX);
    
    state.getField(-1, event.c_str());
    if (state.isNil(-1)) {
        state.pop(1);
        state.createTable(1);
        state.setField(-2, event.c_str());
        
        state.getField(-1, event.c_str());
    }
    
    state.pushValue(func);
    state.setField(-2, id.c_str());
    state.pop(2);
    
    return true;
}

void CallbackHandler::unregisterEvent(lua_State *L, const std::string &event, const std::string &id) {
    LuaState state(L);

    state.push(this);
    state.getTable(LUA_REGISTRYINDEX);

    state.getField(-1, event.c_str());
    if (state.isNil(-1)) {
        return;
    }

    state.push();
    state.setField(-2, id.c_str());
    state.pop(2);
}

void CallbackHandler::call(const std::string &event, std::vector<CallbackArgPtr> &args) {
    LuaState state(state_);
    
    state.push(this);
    state.getTable(LUA_REGISTRYINDEX);
    
    
    state.getField(-1, event.c_str());
    if (state.isNil(-1)) {
        state.pop(2);
        return;
    }
    state.push();
    while (state.next(-2) != 0) {
        for (CallbackArgPtr &arg : args) {
            arg->push(state_);
        }
        if (state.pcall(args.size(), 0) == LUA_ERRRUN) {
            LOGERR << "Error in callback '" << state.tostring(-2) << "' for event '" << event << "': " << state.tostring(-1) << std::endl;
            state.pop(1);
        }
    }

    state.pop(2);
    
    state.getField(LUA_GLOBALSINDEX, "_reload");
    if (state.toBoolean(-1)) {
        AltIrc::get().pluginManager().reload();
    } else {
        state.pop(1);
    }
}

void CallbackHandler::call(const std::string &event, std::initializer_list<CallbackArgPtr> args) {
    std::vector<CallbackArgPtr> vargs;
    vargs.insert(vargs.begin(), args.begin(), args.end());
    call(event, vargs);
}




CallbackArg::CallbackArg() : type_(TNIL) {

}

CallbackArg::CallbackArg(const std::string &string) : type_(TSTRING), string_(string) {

}

CallbackArg::CallbackArg(lua_Number number) : type_(TNUMBER), number_(number) {

}

CallbackArg::CallbackArg(bool boolean) : type_(TBOOLEAN), boolean_(boolean) {

}

void CallbackArg::push(lua_State *L) {
    LuaState state(L);
    switch (type_) {
        case CallbackArg::TSTRING:
            state.push(string_.c_str());
            break;
        case CallbackArg::TNUMBER:
            state.push(number_);
            break;
        case CallbackArg::TINT:
            state.push(int_);
            break;
        case CallbackArg::TBOOLEAN:
            state.push(boolean_);
            break;
        case CallbackArg::TLIGHTUD:
            tolua_pushusertype(L, ud_, udtype_);
            break;
        default:
            state.push();
            break;
    }
}

CallbackArg::CallbackArg(const char *string) : type_(TSTRING), string_(string) {

}

CallbackArg::CallbackArg(lua_Integer in) : type_(TINT), int_(in) {

}

CallbackArgPtr argWrap() {
    return CallbackArgPtr(new CallbackArg);
}

CallbackArgPtr argWrap(const std::string &string) {
    return CallbackArgPtr(new CallbackArg(string));
}

CallbackArgPtr argWrap(lua_Number number) {
    return CallbackArgPtr(new CallbackArg(number));
}

CallbackArgPtr argWrap(const char *string) {
    return CallbackArgPtr(new CallbackArg(string));
}

CallbackArgPtr argWrap(bool boolean) {
    return CallbackArgPtr(new CallbackArg(boolean));
}

CallbackArgPtr argWrap(lua_Integer i) {
    return CallbackArgPtr(new CallbackArg(i));
}