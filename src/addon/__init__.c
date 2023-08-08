#include "__init__.h"
#include "expand_include.h"

static am_addon_t* s_addon_list[] = {
    &am_addon_expand_include,
};

static void _am_addon_load(lua_State* L, void(*cb)(lua_State* L, const char* name, int idx, void* arg), void* arg)
{
    size_t i;
    int sp = lua_gettop(L);

    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1);
        if (cb != NULL)
        {
            cb(L, s_addon_list[i]->name, sp + 1, arg);
        }
        lua_settop(L, sp);
    }
}

static void _addon_foreach(lua_State* L, const char* name, int idx, void* arg)
{
    int* p_ret_idx = (int*)arg;
    int ret_idx = *p_ret_idx;

    lua_pushfstring(L, "[%s]\n", name);
    lua_getfield(L, idx, "desc");
    lua_pushstring(L, "\n");
    lua_concat(L, 3);
    lua_replace(L, ret_idx);
}

void am_addon_init(lua_State* L)
{
    _am_addon_load(L, NULL, NULL);
}

int am_addon_help(lua_State* L)
{
    int sp = lua_gettop(L);
    lua_pushstring(L, ""); // sp+1: this will be the return value

    int idx = sp + 1;
    _am_addon_load(L, _addon_foreach, &idx);

    return 1;
}
