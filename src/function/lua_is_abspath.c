#include "__init__.h"

#define IS_LETTER(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

static int _am_is_abspath(lua_State* L)
{
    int ret = 0;
    const char* path = luaL_checkstring(L, 1);

    if (path[0] == '/')
    {
        ret = 1;
        goto finish;
    }
    if (IS_LETTER(path[0]) && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
        ret = 1;
        goto finish;
    }

finish:
    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_is_abspath = {
"is_abspath", _am_is_abspath, "boolean is_abspath(string path)",
"Check if parameter is absolute path.",
"Check if parameter is absolute path without actually access it."
};
