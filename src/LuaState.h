#ifndef ALTIRC_LUASTATE_H
#define ALTIRC_LUASTATE_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class LuaState {
public:
    LuaState(lua_State *state) : state_(state) {}
    
    inline void call(int nargs, int nresults = LUA_MULTRET) {
        lua_call(state_, nargs, nresults);
    }
    
    inline void close() {
        lua_close(state_);
    }
    
    inline void createTable(int narr = 0, int nrec = 0) {
        lua_createtable(state_, narr, nrec);
    }
    
    inline void getGlobal(const char *name) {
        lua_getglobal(state_, name);
    }
    
    inline void getTable(int index) {
        lua_gettable(state_, index);
    }
    
    inline int getTop() {
        return lua_gettop(state_);
    }
    
    inline bool isBoolean(int index) {
        return lua_isboolean(state_, index) != 0;
    }
    
    inline bool isCFunction(int index) {
        return lua_iscfunction(state_, index) != 0;
    }
    
    inline bool isFunction(int index) {
        return lua_isfunction(state_, index) != 0;
    }
    
    inline bool isLightUserData(int index) {
        return lua_islightuserdata(state_, index) != 0;
    }
    
    inline bool isNil(int index) {
        return lua_isnil(state_, index) != 0;
    }
    
    inline bool isNone(int index) {
        return lua_isnone(state_, index) != 0;
    }
    
    inline bool isNoneOrNil(int index) {
        return lua_isnoneornil(state_, index) != 0;
    }
    
    inline bool isNumber(int index) {
        return lua_isnumber(state_, index) != 0;
    }
    
    inline bool isString(int index) {
        return lua_isstring(state_, index) != 0;
    }
    
    inline bool isTable(int index) {
        return lua_istable(state_, index) != 0;
    }
    
    inline bool isThread(int index) {
        return lua_isthread(state_, index) != 0;
    }
    
    inline bool isUserData(int index) {
        return lua_isuserdata(state_, index) != 0;
    }
    
    inline lua_State *state()  {
        return state_;
    }
    
    inline lua_State *newThread() {
        return lua_newthread(state_);
    }
    
    inline void *newUserData(size_t size) {
        return lua_newuserdata(state_, size);
    }
    
    inline int pcall(int nargs, int nresults = LUA_MULTRET, int errfunc = 0) {
        return lua_pcall(state_, nargs, nresults, errfunc);
    }
    
    inline void pop(int n) {
        lua_pop(state_, n);
    }
    
    inline void push(bool b) {
        lua_pushboolean(state_, b);
    }
    
    inline void push(lua_CFunction fn, int n = 0) {
        lua_pushcclosure(state_, fn, n);
    }
    
    inline void push(lua_Integer n) {
        lua_pushinteger(state_, n);
    }
    
    inline void push(void *p) {
        lua_pushlightuserdata(state_, p);
    } 
    
    inline void push(const char *s) {
        lua_pushstring(state_, s);
    }
    
    inline void push(const char *s, size_t len) {
        lua_pushlstring(state_, s, len);
    }
    
    inline void push() {
        lua_pushnil(state_);
    }
    
    inline void push(lua_Number n) {
        lua_pushnumber(state_, n);
    }
    
    inline int pushThread() {
        return lua_pushthread(state_);
    }
    
    inline void rawget(int index) {
        return lua_rawget(state_, index);
    }
    
    inline void rawgeti(int index, int n) {
        return lua_rawgeti(state_, index, n);
    }
    
    inline void rawset(int index) {
        lua_rawset(state_, index);
    }
    
    inline void rawseti(int index, int n) {
        lua_rawseti(state_, index, n);
    }
    
    inline int resume(int narg) {
        return lua_resume(state_, narg);
    }
    
    inline void setGlobal(const char *name) {
        lua_setglobal(state_, name);
    }
    
    inline void setTable(int index) {
        lua_settable(state_, index);
    }
    
    inline bool toBoolean(int index) {
        return lua_toboolean(state_, index);
    }
    
    inline lua_CFunction toCFunction(int index) {
        return lua_tocfunction(state_, index);
    }
    
    inline lua_Integer toInteger(int index) {
        return lua_tointeger(state_, index);
    }
    
    inline const char *tostring(int index, size_t *len = NULL) {
        return lua_tolstring(state_, index, len);
    }
    
    inline lua_Number toNumber(int index) {
        return lua_tonumber(state_, index);
    }
    
    inline const void *toPointer(int index) {
        return lua_topointer(state_, index);
    }
    
    inline lua_State *toThread(int index) {
        return lua_tothread(state_, index);
    }
    
    inline void *toUserData(int index) {
        return lua_touserdata(state_, index);
    }
    
    inline int type(int index) {
        return lua_type(state_, index);
    }
    
    inline const char *typeName(int tp) {
        return lua_typename(state_, tp);
    }
    
    inline void argCheck(bool cond, int narg, const char *extramsg) {
        luaL_argcheck(state_, cond, narg, extramsg);
    }
    
    inline int checkInt(int narg) {
        return luaL_checkint(state_, narg);
    }
    
    inline long checkLong(int narg) {
        return luaL_checklong(state_, narg);
    }
    
    inline const char *checkstring(int narg, size_t *l = NULL) {
        return luaL_checklstring(state_, narg, l);
    }
    
    inline lua_Number checkNumber(int narg) {
        return luaL_checknumber(state_, narg);
    }
    
    inline void checkType(int narg, int t) {
        luaL_checktype(state_, narg, t);
    }
    
    inline void *checkUserData(int narg, const char *tname) {
        return luaL_checkudata(state_, narg, tname);
    }
    
    inline int loadString(const char *s) {
        return luaL_loadstring(state_, s);
    }
    
    inline void openLibs() {
        luaL_openlibs(state_);
    }
    
    inline void getField(int index, const char *k) {
        lua_getfield(state_, index, k);
    }
    
    inline void setField(int index, const char *k) {
        lua_setfield(state_, index, k);
    }
    
    inline void pushValue(int index) {
        lua_pushvalue(state_, index);
    }
    
    inline int next(int index) {
        return lua_next(state_, index);
    }
    
private:
    lua_State *state_;
};




#endif //ALTIRC_LUASTATE_H
