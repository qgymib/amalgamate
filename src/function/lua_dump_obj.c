#include "__init__.h"

static int _am_dump_obj(lua_State* L)
{
    if (lua_type(L, 1) != LUA_TTABLE)
    {
        lua_getglobal(L, "tostring");
        lua_pushvalue(L, 1);
        lua_call(L, 1, 1);
        return 1;
    }

    int sp = lua_gettop(L);
    lua_pushstring(L, "{ "); // sp+1: return value

    lua_pushnil(L); // sp+2
    while (lua_next(L, 1) != 0) // sp+3
    {
        lua_pushvalue(L, sp + 1);
        lua_pushstring(L, "[");

        if (lua_type(L, sp + 2) != LUA_TNUMBER)
        {
            lua_pushstring(L, "\"");
            lua_pushvalue(L, sp + 2);
            lua_pushstring(L, "\"");
            lua_concat(L, 3);
        }
        else
        {
            lua_pushvalue(L, sp + 2);
        }
        lua_pushstring(L, "] = ");

        lua_pushcfunction(L, _am_dump_obj);
        lua_pushvalue(L, sp + 3);
        lua_call(L, 1, 1);

        lua_pushstring(L, ",");

        lua_concat(L, 6);
        lua_replace(L, sp + 1);

        lua_pop(L, 1);
    }

    lua_pushstring(L, "} ");
    lua_concat(L, 2);

    return 1;
}

am_function_t am_f_dump_obj = {
"dump_obj",_am_dump_obj, "string dump_obj(object o)",
"Dump object as string.",
"Dump object as string."
};
