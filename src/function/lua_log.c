#include "lua_log.h"
#include "lua_file.h"
#include <string.h>

static int _log_i(lua_State* L)
{
    int sp = lua_gettop(L);
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Format string */
    lua_getglobal(L, "string"); //sp+1
    lua_getfield(L, -1, "format"); //sp+2
    lua_remove(L, sp + 1);
    lua_insert(L, 1);
    lua_call(L, sp, 1); // sp=1
    luaL_checktype(L, 1, LUA_TSTRING);

    /* Write to logfile */
    lua_Debug ar; memset(&ar, 0, sizeof(ar));
    lua_getstack(L, 1, &ar);
    lua_getinfo(L, "nSl", &ar);

    lua_pushcfunction(L, am_func_append_file.func); // sp=2

    lua_getglobal(L, "arg"); // sp=3
    lua_getfield(L, -1, "logfile"); //sp=4
    lua_remove(L, 3); // sp=3

    lua_pushfstring(L, "[%s:%d] ", ar.source, ar.currentline); // sp=4
    lua_pushvalue(L, 1); // sp=5
    lua_pushstring(L, "\n"); // sp=6
    lua_concat(L, 3); // sp=4

    lua_call(L, 2, 0); // sp=1

    return 0;
}

am_function_t am_func_log_i = {
"log_i", _log_i, "nil log_i(string data)",
"Append data into log file.",
"Append data into log file."
};
