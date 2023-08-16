#include "__init__.h"

static int _am_load_txt_file(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* file_type = "\n";
    if (lua_type(L, 2) == LUA_TSTRING)
    {
        file_type = lua_tostring(L, 2);
    }

    /* Load file */
    lua_pushcfunction(L, am_f_load_file.addr);
    lua_pushvalue(L, 1);
    lua_call(L, 1, 1); // sp+1

    /* Split line */
    lua_pushcfunction(L, am_f_split_line.addr);
    lua_insert(L, sp + 1);
    lua_call(L, 1, 1); // sp+1

    lua_pushcfunction(L, am_f_merge_line.addr);
    lua_insert(L, sp + 1);
    lua_pushstring(L, file_type);
    lua_call(L, 2, 1); // sp+1

    return 1;
}

am_function_t am_f_load_txt_file = {
"load_txt_file", _am_load_txt_file, "string load_txt_file(string path)",
"Load while file as txt mode and return it.",
"Load while file as txt mode and return it. Line endings is always convert to \"\\n\"."
};
