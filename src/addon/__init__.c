#include "__init__.h"
#include <string.h>

static am_addon_t* s_addon_list[] = {
    &am_a_c_dump_hex,
    &am_a_c_expand_include,
    &am_a_txt_black_hole,
    &am_a_txt_pcre2_substitute,
};

typedef void (*am_addon_load_cb)(lua_State* L, const char* name, int idx, void* arg);

/**
 * @brief Load all addons.
 * @param[in] L     Lua VM.
 * @param[in] cb    Load callback. Can be NULL.
 * @param[in] arg   User data passed to \p cb.
 */
static void _am_addon_load(lua_State* L, am_addon_load_cb cb, void* arg)
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

    lua_pushvalue(L, ret_idx);
    lua_pushfstring(L, "%s\n    ", name);
    if (lua_getfield(L, idx, "brief") != LUA_TSTRING)
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NO BRIEF");
    }
    lua_pushstring(L, "\n");
    lua_concat(L, 4);
    lua_replace(L, ret_idx);
}

void am_addon_init(lua_State* L)
{
    _am_addon_load(L, NULL, NULL);
}

int am_addon_list(lua_State* L)
{
    int sp = lua_gettop(L);

    lua_pushstring(L, ""); // sp+1: this will be the return value
    int idx = sp + 1;

    _am_addon_load(L, _addon_foreach, &idx);

    return 1;
}

static void _addon_manual(lua_State* L, const char* name, int ret_idx, int req_idx)
{
    /* NAME */
    lua_pushfstring(L, "[NAME]\n%s\n\n", name);

    /* BRIEF */
    lua_pushstring(L, "[BRIEF]\n");
    if (lua_getfield(L, req_idx, "brief") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n\n");
    }
    lua_concat(L, 2);

    /* DOCUMENT */
    lua_pushstring(L, "[DOCUMENT]\n");
    if (lua_getfield(L, req_idx, "desc") == LUA_TSTRING)
    {
        lua_pushstring(L, "\n");
        lua_concat(L, 2);
    }
    else
    {
        lua_pop(L, 1);
        lua_pushstring(L, "NONE\n");
    }
    lua_concat(L, 2);

    /* Merge string */
    lua_concat(L, 3);

    /* Set return value */
    lua_replace(L, ret_idx);
}

int am_addon_manual(lua_State* L)
{
    int sp = lua_gettop(L);
    const char* name = luaL_checkstring(L, 1);

    lua_pushstring(L, ""); // sp+1: return value.

    size_t i;
    for (i = 0; i < ARRAY_SIZE(s_addon_list); i++)
    {
        if (strcmp(name, s_addon_list[i]->name) == 0)
        {
            luaL_requiref(L, s_addon_list[i]->name, s_addon_list[i]->open, 1); // sp+2
            _addon_manual(L, name, sp + 1, sp + 2);
            lua_pop(L, 1);
            return 1;
        }
    }

    return 0;
}

int am_addon_call_script(lua_State* L, const char* script, const char* name)
{
    if (luaL_loadbuffer(L, script, strlen(script), name) != LUA_OK)
    {
        return lua_error(L);
    }

    lua_call(L, 0, 1);
    return 1;
}
