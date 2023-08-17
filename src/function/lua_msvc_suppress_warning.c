#include "__init__.h"

static int _msvc_suppress_warning(lua_State* L)
{
    int i;
    int sp = lua_gettop(L);

    if (sp <= 1)
    {
        return sp;
    }
    luaL_checktype(L, 1, LUA_TSTRING);

    lua_pushstring(L, "#if defined(_MSC_VER)\n#pragma warning(push)\n");

    for (i = 2; i <= sp; i++)
    {
        lua_pushstring(L, "#pragma warning(disable : ");
        lua_pushvalue(L, sp);
        lua_pushstring(L, ")\n");
        lua_concat(L, 4);
    }

    lua_pushstring(L, "#endif\n");
    lua_concat(L, 2);

    lua_pushvalue(L, 1);
    lua_concat(L, 2);

    lua_pushstring(L, "#if defined(_MSC_VER)\n#pragma warning(pop)\n#endif\n");
    lua_concat(L, 2);

    return 1;
}

am_function_t am_f_msvc_suppress_warning = {
"msvc_suppress_warning", _msvc_suppress_warning, "string msvc_suppress_warning(string source[, int code1, ...])",
"Suppress warning for MSVC cl compiler.",
"Suppress warning for MSVC cl compiler."
};
