#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "amalgamate.h"

static int _main(lua_State* L)
{
    luaL_openlibs(L);

    int argc = (int)lua_tointeger(L, 1);
    char** argv = lua_touserdata(L, 2);
    
    amalgamate_ctx_t* ctx = amalgamate_make(L, argc, argv);
    lua_setglobal(L, "amalgamate");

    lua_pushinteger(L, amalgamate_run(L, ctx));
    return 1;
}

int main(int argc, char* argv[])
{
    int ret = 0;
    lua_State* L = luaL_newstate();

    lua_pushcfunction(L, _main);
    lua_pushinteger(L, argc);
    lua_pushlightuserdata(L, argv);
    if ((ret = lua_pcall(L, 2, 1, 0)) != LUA_OK)
    {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        goto finish;
    }

    ret = (int)lua_tointeger(L, -1);

finish:
    lua_close(L);
    return ret;
}
