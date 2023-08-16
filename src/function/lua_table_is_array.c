#include "__init__.h"

static int am_table_is_array(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    int ret = 0;
    if (lua_geti(L, 1, 1) != LUA_TNIL)
    {
        ret = 1;
    }
    lua_pop(L, 1);

    lua_pushboolean(L, ret);
    return 1;
}

am_function_t am_f_table_is_array = {
"table_is_array", am_table_is_array, "boolean table_is_array(table t)",
"Check if a Lua table is array.",

"Check if parameter `t` is an array."
};
