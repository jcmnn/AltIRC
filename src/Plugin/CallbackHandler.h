#ifndef ALTIRC_CALLBACKHANDLER_H
#define ALTIRC_CALLBACKHANDLER_H

#include "../LuaState.h"
#include "tolua++.h"
#include <string>
#include <vector>
#include <memory>

class CallbackArg;
typedef std::shared_ptr<CallbackArg> CallbackArgPtr;

class CallbackArg {
public:
    CallbackArg();
    CallbackArg(const std::string &string);
    CallbackArg(const char *string);
    CallbackArg(lua_Number number);
    CallbackArg(bool boolean);
    CallbackArg(lua_Integer i);
    
    template<class T>
    CallbackArg(T *t, const char *name);
    
    virtual void push(lua_State *state);

private:
    enum ArgType {
        TSTRING,
        TNUMBER,
        TBOOLEAN,
        TLIGHTUD,
        TINT,
        TNIL
    };
    
    union {
        lua_Number number_;
        lua_Integer int_;
        bool boolean_;
        struct {
            void *ud_;
            const char *udtype_;
        };
    };
    
    std::string string_;
    ArgType type_;
};

CallbackArgPtr argWrap();

CallbackArgPtr argWrap(const std::string &string);

CallbackArgPtr argWrap(lua_Number number);

CallbackArgPtr argWrap(const char *string);

CallbackArgPtr argWrap(bool boolean);

template<class T>
CallbackArgPtr argWrap(T *t, const char *name) {
    return CallbackArgPtr(new CallbackArg(t, name));
}

CallbackArgPtr argWrap(lua_Integer i);



template<class T>
class CallbackClassArg : public CallbackArg {
public:
    CallbackClassArg(const T &t, const char *type);
    CallbackClassArg(T &&t, const char *type);
    
    void push(lua_State *state) override;
private:
    T t_;
    const char *type_;
};

template<class T>
CallbackClassArg<T>::CallbackClassArg(const T &t, const char *type) : t_(t), type_(type) {
    
}

template<class T>
CallbackClassArg<T>::CallbackClassArg(T &&t, const char *type) : t_(std::move(t)), type_(type) {

}

template<class T>
void CallbackClassArg<T>::push(lua_State *L) {
    tolua_pushusertype(L, &t_, type_);
}

template<class T>
CallbackArgPtr argWrap(const T &t, const char *type) {
    return CallbackArgPtr(new CallbackClassArg<T>(t, type));
}

template<class T>
CallbackArgPtr argWrap(T &&t, const char *type) {
    return CallbackArgPtr(new CallbackClassArg<T>(std::move(t), type));
}



class CallbackHandler { // tolua_export
public:
    CallbackHandler();
    void initialize(lua_State *state);

    /* Calls event with arguments */
    void call(const std::string &event, std::initializer_list<CallbackArgPtr> args = {});
    void call(const std::string &event, std::vector<CallbackArgPtr> &args);
    
    // tolua_begin
    /* Registers fn to an event */
    bool registerEvent(lua_State *state, const std::string &event, const std::string &id, lua_Object func);
    
    /* Unregisters an event handler */
    void unregisterEvent(lua_State *state, const std::string &event, const std::string &id);
    // tolua_end
private:
    lua_State *state_;
}; // tolua_export


template<class T>
CallbackArg::CallbackArg(T *t, const char *name) : type_(TLIGHTUD), ud_(t), udtype_(name) {

}

#endif //ALTIRC_CALLBACKHANDLER_H
